using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class SignupResponse
    {
        private int _status;

       public SignupResponse(int status)
        {
            _status = status;
        }

        public int GetStatus()
        {
            return _status;
        }

    }
}
