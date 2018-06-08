using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class JoinRoomRequest
    {
        private int id;
        public JoinRoomRequest(int id)
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
