using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class SendResultsResponse
    {
        int _position;
        string _winner;
        SendResultsResponse(int position, string winner)
        {
            _position = position;
            _winner = winner;
        }

        public int GetPosition()
        {
            return _position;
        }

        public string GetWinner()
        {
            return _winner;
        }
    }
}
