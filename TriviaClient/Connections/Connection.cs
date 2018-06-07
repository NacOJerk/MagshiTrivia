﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.infrastructure;
using TriviaClient.Events;
using TriviaClient.Utils;
using System.Net.Sockets;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Threading;

namespace TriviaClient.Connections
{
    delegate void Handle(Response response, Connection con);
    class Connection
    {
        private PipeManager pipe;
        private TcpClient client;
        private ListenerWrap wrap;
        private Object reciveLock;
        private Object sendLock;

        public Connection(string addr, int port, PipeManager mang, IPacketListener pack = null)
        { 
            //We start by trying to connect to the server
            client = new TcpClient();
            client.Connect(addr, port);
            reciveLock = new Object();
            sendLock = new Object();
            pipe = mang;
            if(pack != null)
                wrap = new ListenerWrap(pack);
            dynamic thread = new Thread(Reciver);
            thread.Start();
        }

        [MethodImpl(MethodImplOptions.Synchronized)]
        public void SetListener(IPacketListener pack)
        {
            if (pack == null)
                wrap = null;
            else
                wrap = new ListenerWrap(pack);
        }

        public void Send(byte[] data)
        {
            lock (sendLock)
            {
                pipe.Send(client.Client, data);
            }
        }

        public Response Recive()
        {
            Response r = null;
            lock(reciveLock)
            {
                r = pipe.Read(client.Client);
            }
            return r;
        }

        public void Send(byte[] data, Handle handler)
        {
            Response r = null;
            lock (reciveLock)
            {
                Send(data);
                r = pipe.Read(client.Client);
            }
            handler(r, this);
        }

        private void Reciver()
        {
            while(client.Connected)
            {
                if (wrap == null)
                    continue;
                Response resp = Recive();
                bool handled = wrap.Invoke(resp, this);
                if(!handled)
                {
                    Console.WriteLine("Unhandled packet " + resp.GetID());
                }
            }
        }


        private class ListenerWrap
        {
            private IPacketListener listener;
            private Dictionary<ResponseID, Handle> functions;

            public ListenerWrap(IPacketListener listener)
            {
                this.listener = listener;
                functions = new Dictionary<ResponseID, Handle>();
                Type type = listener.GetType();
                foreach(MethodInfo mInfo in type.GetMethods())
                {
                    if(Attribute.IsDefined(mInfo, typeof(PacketHandler)) && mInfo.IsPublic)
                    {
                        ParameterInfo[] parms = mInfo.GetParameters();
                        if(parms.Length == 2 && parms[0].ParameterType == typeof(Response) && parms[1].ParameterType == typeof(Connection))
                        {
                            //Ready to add this boyyyy
                            //We first create a delegate
                            Delegate del = Delegate.CreateDelegate(typeof(Handle), listener, mInfo, false);
                            if(del != null)
                            {
                                //Lets get some info doe
                                PacketHandler data = mInfo.GetCustomAttribute<PacketHandler>();
                                Handle handl = (Handle) del;
                                functions.Add(data.GetID(), handl);
                            }
                        }
                    }
                }
            }

            public bool Invoke(Response resp, Connection con)
            {
                if (!functions.ContainsKey(resp.GetID()))
                {
                    return false;
                }
                functions[resp.GetID()](resp, con);
                return true;
            }


        }
    }
}