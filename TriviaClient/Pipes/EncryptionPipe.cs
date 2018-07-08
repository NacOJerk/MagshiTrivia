using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RSA;
using TriviaClient.infrastructure;

namespace TriviaClient.Pipes
{
    class EncryptionPipe : IPipe
    {
        private Key _key;

        public EncryptionPipe(Key k)
        {
            _key = k;
        }

        public byte[] Read(byte[] buff)
        {
            List<byte> buf = new List<byte>(buff);
            return RSA.RSA.Decrypt(buf, _key).ToArray();
        }

        public byte[] Write(byte[] buff)
        {
            List<byte> buf = new List<byte>(buff);
            return RSA.RSA.Encrypt(buf, _key).ToArray();
        }
    }
}
