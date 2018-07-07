using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Requests
{
    class CreateRoomRequest
    {
        [JsonProperty(PropertyName = "username")]
        private string username;
        [JsonProperty(PropertyName = "maxUsers")]
        private int maxUsers;
        [JsonProperty(PropertyName = "questionCount")]
        private int questionCount;
        [JsonProperty(PropertyName = "answerTimeout")]
        private int answerTimeout;

        public CreateRoomRequest(string username, int maxUsers, int questionCount, int answerTimeout)
        {
            this.username = username;
            this.questionCount = questionCount;
            this.maxUsers = maxUsers;
            this.answerTimeout = answerTimeout;
        }

        public string GetUsername()
        {
            return username;
        }

        public int GetMaxUsers()
        {
            return maxUsers;
        }

        public int GetQuestionCount()
        {
            return questionCount;
        }

        public int GetAnswerTimeout()
        {
            return answerTimeout;
        }
    }
}
