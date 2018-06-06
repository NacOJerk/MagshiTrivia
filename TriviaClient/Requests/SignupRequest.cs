using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class SignupRequest
    {
        private string _username, _password, _email;

        public SignupRequest(string username, string password, string email)
        {
            _username = username;
            _password = password;
            _email = email;
        }

        public string GetUsername()
        {
            return _username;
        }

        public string GetPassword()
        {
            return _password;
        }

        public string GetEmail()
        {
            return _email;
        }

    }
}
