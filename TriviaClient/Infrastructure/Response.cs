using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Utils;

namespace TriviaClient.infrastructure
{
    class Response
    {
        private ResponseID _id;
        private byte[] _buffer;

        public Response(ResponseID id, byte[] buffer)
        {
            _id = id;
            _buffer = buffer;
            
        }

        public ResponseID GetID()
        {
            return _id;
        }

        public byte[] GetBuffer()
        {
            return _buffer;
        }

    }
}
