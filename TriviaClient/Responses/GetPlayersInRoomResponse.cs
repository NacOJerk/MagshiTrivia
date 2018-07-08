using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    public class GetPlayersInRoomResponse
    {
        private string[] players;
        private int max_players;
        public GetPlayersInRoomResponse(string[] players, int max_players)
        {
            this.players = players;
            this.max_players = max_players;
        }

        public string[] GetPlayers()
        {
            return players;
        }

        public int GetMaxPlayers()
        {
            return max_players;
        }

    }
}
