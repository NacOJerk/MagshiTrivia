using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Requests
{
    class JoinRoomRequest
    {
        [JsonProperty(PropertyName ="id")]
        private int id;
        public JoinRoomRequest(int id)
        {
            this.id = id;
        }

        public int GetId()
        {
            return id;
        }
    }
}
