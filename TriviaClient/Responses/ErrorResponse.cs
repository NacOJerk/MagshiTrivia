using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class ErrorResponse
    {
        private string _message;

        public ErrorResponse(string message)
        {
            _message = message;
        }

        public string GetMessage()
        {
            return _message;
        }

    }
}
