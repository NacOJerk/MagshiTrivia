using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class CreateRoomResponse
    {
        private int id;
        public CreateRoomResponse(int id)
        {
            this.id = id;
        }
        
        public int GetID()
        {
            return id;
        }
    }
}
