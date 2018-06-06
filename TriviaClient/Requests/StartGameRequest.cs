using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class StartGameRequest
    {
        private int id;
        public StartGameRequest(int id)
        {
            this.id = id;
        }

        public int GetId()
        {
            return id;
        }
    }
}
