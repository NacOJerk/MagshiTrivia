using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Requests
{
    class StartGameRequest
    {
        [JsonProperty(PropertyName ="id")]
        private int id;
        public StartGameRequest(int id)
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
