using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class CloseRoomRequest
    {
        private int id;
        public CloseRoomRequest(int id)
        {
            this.id = id;
        }

        public int GetId()
        {
            return id;
        }
    }
}
