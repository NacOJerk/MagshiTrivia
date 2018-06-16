using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.infrastructure
{
    class Room
    {
        private int id, questionCount, answerTimeout, maxPlayers, numPlayers;
        private string admin;
        
        public Room(string admin, int id, int questionCount, int answerTimeout, int numPlayers, int maxPlayers)
        {
            this.admin = admin;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
            this.maxPlayers = maxPlayers;
            this.numPlayers = numPlayers;
            this.id = id;
        }

        public int GetID()
        {
            return id;
        }

        public int GetQuestionCount()
        {
            return questionCount;
        }

        public int GetAnswerTimeout()
        {
            return answerTimeout;
        }

        public int GetNumPlayers()
        {
            return numPlayers;
        }

        public int GetMaxPlayers()
        {
            return maxPlayers;
        }

        public string GetAdmin()
        {
            return admin;
        }
    }
}
