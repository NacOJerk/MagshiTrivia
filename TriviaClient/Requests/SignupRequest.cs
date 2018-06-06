using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class SignupRequest
    {
        private string username, password, email;

        public SignupRequest(string username, string password, string email)
        {
            this.username = username;
            this.password = password;
            this.email = email;
        }

        public string GetUsername()
        {
            return username;
        }

        public string GetPassword()
        {
            return password;
        }

        public string GetEmail()
        {
            return email;
        }

    }
}
