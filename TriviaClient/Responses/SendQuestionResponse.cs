using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class SendQuestionResponse
    {
        string _question;
        string[] _answer;
        uint _remaining;

        SendQuestionResponse(string question, string[] answers, uint remaining)
        {
            _question = question;
            _answer = answers;
            _remaining = remaining;
        }

        public string GetQuestion()
        {
            return _question;
        }

        public string[] GetAnswers()
        {
            return _answer;
        }
    }
}
