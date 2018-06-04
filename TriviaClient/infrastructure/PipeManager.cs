using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using TriviaClient.Utils;

namespace TriviaClient.infrastructure
{
    class PipeManager
    {
        private List<IPipe> _pipes;
        public PipeManager()
        {
            _pipes = new List<IPipe>();
        }

        public void AddPipe(IPipe pipe)
        {
            _pipes.Add(pipe);
        }

        public void Send(Socket sock, byte[] buff)
        {
            foreach (IPipe pipe in _pipes)
                buff = pipe.Write(buff);
            byte[] data = new byte[buff.Length + 4];
            int len = buff.Length;
            data[0] = (byte)(len & 255);
            data[1] = (byte)(len >> 8 & 255);
            data[2] = (byte)(len >> 16 & 255);
            data[3] = (byte)(len >> 24 & 255);
            for (int i = 0; i < buff.Length; data[i + 4] = buff[i], i++) ;
            while(data.Length > 0)
            {
                int sent = sock.Send(data);
                byte[] data2 = new byte[data.Length - sent];
                for (int i = sent; i < data.Length; data2[i - sent] = data[sent], i++) ;
                data = data2;
            }
        }

        public Request Read(Socket sock)
        {
            byte[] len = new byte[4];
            sock.Receive(len);
            int length = len[0] | len[1] << 8 | len[2] << 16 | len[3] << 24;
            byte[] data = new byte[length];
            sock.Receive(data);
            foreach (IPipe pipe in _pipes.Reverse<IPipe>())
                data = pipe.Read(data);
            RequestID id = (RequestID) data[0];
            length = data[1] | data[2] << 8 | data[3] << 16 | data[4] << 24;
            if (length != data.Length - 5)
                throw new Exception("Invaild Packet");
            byte[] buff = new byte[data.Length - 5];
            for (int i = 0; i < buff.Length; buff[i] = data[i + 5] , i++) ;
            return new Request(id, buff);
        }

    }
}
