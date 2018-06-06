using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Requests
{
    class CreateRoomRequest
    {
        private string username;
        private int maxUsers, questionCount, answerTimeout;

        public CreateRoomRequest(string username, int questionCount, int maxUsers, int answerTimeout)
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
