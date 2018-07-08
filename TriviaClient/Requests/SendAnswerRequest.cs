using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Requests
{
    class SendAnswerRequest
    {
        [JsonProperty(PropertyName ="answer")]
        private uint _answer;

        public SendAnswerRequest(uint answer)
        {
            _answer = answer;
        }

        public uint GetAnswer()
        {
            return _answer;
        }
    }
}
