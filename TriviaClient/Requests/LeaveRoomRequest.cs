using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class LeaveRoomRequest
    {
        private int id;
        public LeaveRoomRequest(int id)
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
