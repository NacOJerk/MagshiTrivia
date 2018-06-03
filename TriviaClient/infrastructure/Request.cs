using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Utils;

namespace TriviaClient.infrastructure
{
    class Request
    {
        private RequestID _id;
        private byte[] _buffer;

        public Request(RequestID id, byte[] buffer)
        {
            _id = id;
            _buffer = buffer;
        }

        public RequestID GetID()
        {
            return _id;
        }

        public byte[] GetBuffer()
        {
            return _buffer;
        }

    }
}
