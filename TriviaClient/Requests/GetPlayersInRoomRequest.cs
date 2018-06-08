using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class GetPlayersInRoomRequest
    {
        private int id;
        public GetPlayersInRoomRequest(int id)
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
