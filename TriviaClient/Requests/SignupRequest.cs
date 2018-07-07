using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Requests
{
    class SignupRequest
    {
        [JsonProperty(PropertyName ="username")]
        private string username;
        [JsonProperty(PropertyName = "password")]
        private string password;
        [JsonProperty(PropertyName = "email")]
        private string email;

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
