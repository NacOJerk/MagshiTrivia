using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class GetRoomStateRequest
    {
        private int id;
        public GetRoomStateRequest(int id)
        {
            this.id = id;
        }

        public int GetId()
        {
            return id;
        }
    }
}
