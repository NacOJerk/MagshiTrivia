using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class SendAnswerResponse
    {
        private uint _status;

        public SendAnswerResponse(uint status)
        {
            _status = status;
        }

        public uint GetStatus()
        {
            return _status;
        }
    }
}
