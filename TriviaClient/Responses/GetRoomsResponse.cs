using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.infrastructure;

namespace TriviaClient.Responses
{
    class GetRoomsResponse
    {
        private int status;
        private Room[] rooms;
        public GetRoomsResponse(Room[] rooms, int status)
        {
            this.rooms = rooms;
            this.status = status;
        }

        public Room[] GetRooms()
        {
            return rooms;
        }

        public int GetStatus()
        {
            return status;
        }
    }
}
