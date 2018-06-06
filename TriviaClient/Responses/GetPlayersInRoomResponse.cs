using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class GetPlayersInRoomResponse
    {
        private string[] _players;

        public GetPlayersInRoomResponse(string[] players)
        {
            _players = players;
        }

        public string[] GetPlayers()
        {
            return _players;
        }
    }
}
