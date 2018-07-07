using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class JoinRoomResponse
    {
        private int status;
        public JoinRoomResponse(int status)
        {
            this.status = status;
        }
        public int GetStatus()
        {
            return status;
        }
    }
}
