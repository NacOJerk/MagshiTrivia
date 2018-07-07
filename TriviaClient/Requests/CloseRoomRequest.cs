using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
namespace TriviaClient.Requests
{
    class CloseRoomRequest
    {
        [JsonProperty(PropertyName = "id")]
        private int id;
        public CloseRoomRequest(int id)
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
