using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class LoginRequest
    {
        private string username, password;

        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }

        public string GetUsername()
        {
            return username;
        }

        public string GetPassword()
        {
            return password;
        }

    }
}
