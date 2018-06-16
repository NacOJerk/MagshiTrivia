using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Requests
{
    class LoginRequest
    {
        [JsonProperty(PropertyName ="username")]
        private string username;
        [JsonProperty(PropertyName ="password")]
        private string password;

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
