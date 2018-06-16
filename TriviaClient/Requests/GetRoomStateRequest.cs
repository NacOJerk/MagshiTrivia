using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Requests
{
    class GetRoomStateRequest
    {
        [JsonProperty(PropertyName ="id")]
        private int id;
        public GetRoomStateRequest(int id)
        {
            this.id = id;
        }

        public int GetId()
        {
            return id;
        }

        public string ToString()
        {
            return "{\"id\": " + id + "}";
        }
    }
}
