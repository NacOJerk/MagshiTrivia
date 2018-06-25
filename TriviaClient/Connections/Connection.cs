using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Threads;
using TriviaClient.infrastructure;
using TriviaClient.Events;
using TriviaClient.Utils;
using System.Net.Sockets;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Collections.Generic;

namespace TriviaClient.Connections
{
    delegate void Handle(PacketEvent e);

    class Connection
    {
        private PipeManager pipe;
        private TcpClient client;
        private ListenerWrap wrap;
        private Object sendLock;
        private UserData userData;
        private MainWindow window;
        private TriviaClient.Threads.ThreadPriority priority;
        private Deque<Response> responses;

        public Connection(string addr, int port, PipeManager mang,MainWindow window, IPacketListener pack = null)
        { 
            //We start by trying to connect to the server
            client = new TcpClient();
            client.Connect(addr, port);
            sendLock = new Object();
            pipe = mang;
            if(pack != null)
                wrap = new ListenerWrap(pack);
            userData = new UserData();
            this.window = window;
            priority = new Threads.ThreadPriority();
            responses = new Deque<Response>();

            dynamic recive = new Thread(Reciver);
            recive.Start();
            dynamic handle = new Thread(Handler);
            handle.Start();

        }

        public UserData GetData()//Totally not thread safe yet doe I will just make it safe inside of the object
        {
            return userData;
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

        public void Send(byte[] data, Handle handler)
        {
            Response r = null;
            lock(priority.Lock)
            {
                Send(data);
                priority.WaitFirst();
                if (responses.IsEmpty())
                    throw new Exception("Some thing went horribly wrong");
                r = responses.PopBack();
            }
            handler(new PacketEvent(this, r, window));
        }

        private void Handler()
        {
            while(client.Connected)
            {
                if (wrap == null)
                    continue;
                lock(priority.Lock)
                {
                    priority.WaitLast();
                    while(!responses.IsEmpty())
                    {
                        Response resp = responses.PopFront();
                        bool handled = wrap.Invoke(resp, this, window);
                        if (!handled)
                        {
                            Console.WriteLine("Unhandled packet " + resp.GetID());
                        }
                    }
                }
            }
        }

        private void Reciver()
        {
            while(client.Connected)
            {
                lock(priority.Lock)
                {
                    responses.AddBackward(pipe.Read(client.Client));
                    priority.PulseAll();
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
                        if(parms.Length == 1 && parms[0].ParameterType == typeof(PacketEvent))
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

            public bool Invoke(Response resp, Connection con, MainWindow window)
            {
                if (!functions.ContainsKey(resp.GetID()))
                {
                    return false;
                }
                functions[resp.GetID()](new PacketEvent(con, resp, window));
                return true;
            }


        }
    }
}
