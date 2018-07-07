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

        public void ClearPipes()
        {
            _pipes.Clear();
        }

        public void Send(Socket sock, byte[] buff)
        {
            foreach (IPipe pipe in _pipes)
                buff = pipe.Write(buff);
            byte[] data = new byte[buff.Length + 4];
            int len = buff.Length;
            data[3] = (byte)(len & 255);
            data[2] = (byte)(len >> 8 & 255);
            data[1] = (byte)(len >> 16 & 255);
            data[0] = (byte)(len >> 24 & 255);
            Console.WriteLine(len);
            for (int i = 0; i < buff.Length; data[i + 4] = buff[i], i++) ;
            while(data.Length > 0)
            {
                Console.WriteLine(data.Length);
                int sent = sock.Send(data);
                Console.WriteLine(sent);
                byte[] data2 = new byte[data.Length - sent];
                for (int i = sent; i < data.Length; data2[i - sent] = data[sent], i++) ;
                data = data2;
                Console.WriteLine(data.Length);
            }
        }

        private byte[] ReceiveLargeFile(Socket socket, uint lenght)
        {
            // send first the length of total bytes of the data to server
            // create byte array with the length that you've send to the server.
            byte[] data = new byte[lenght];


            uint size = lenght; // lenght to reveive
            var total = 0; // total bytes to received
            var dataleft = (int)size; // bytes that havend been received 

            // 1. check if the total bytes that are received < than the size you've send before to the server.
            // 2. if true read the bytes that have not been receive jet
            while (total < size)
            {
                // receive bytes in byte array data[]
                // from position of total received and if the case data that havend been received.
                var recv = socket.Receive(data, total, dataleft, SocketFlags.None);
                if (recv == 0) // if received data = 0 than stop reseaving
                {
                    data = null;
                    break;
                }
                total += recv;  // total bytes read + bytes that are received
                dataleft -= recv; // bytes that havend been received
            }
            return data; // return byte array and do what you have to do whith the bytes.
        }

        public Response Read(Socket sock)
        {
            byte[] len = ReceiveLargeFile(sock, 4);
            uint length = BitConverter.ToUInt32(
                   BitConverter.IsLittleEndian
                   ? len.Reverse().ToArray()
                   : len, 0);
            Console.Write("Data to read is said to be " + length);
            byte[] data = ReceiveLargeFile(sock, length);
            foreach (IPipe pipe in _pipes.Reverse<IPipe>())
                data = pipe.Read(data);
            ResponseID id = (ResponseID) data[0];
            for (int i = 0; i < 4; len[i] = data[i + 1], i++) ;
            length = BitConverter.ToUInt32(
                  BitConverter.IsLittleEndian
                  ? len.Reverse().ToArray()
                  : len, 0);
            if (length != data.Length - 5)
                throw new Exception("Invaild Packet");
            byte[] buff = new byte[data.Length - 5];
            for (int i = 0; i < buff.Length; buff[i] = data[i + 5] , i++) ;
            return new Response(id, buff);
        }

        public byte[] ReadPacket(Socket sock)
        {
            byte[] len = ReceiveLargeFile(sock, 4);
            uint length = BitConverter.ToUInt32(
                  BitConverter.IsLittleEndian
                  ? len.Reverse().ToArray()
                  : len, 0);
            byte[] data = ReceiveLargeFile(sock, length);
            foreach (IPipe pipe in _pipes.Reverse<IPipe>())
                data = pipe.Read(data);
            return data;
        }

    }
}
