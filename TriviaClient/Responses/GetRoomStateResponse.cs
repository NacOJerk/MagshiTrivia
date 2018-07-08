using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class GetRoomStateResponse
    {
        private int status;
        private bool has_game_begun;
        private string[] players;
        private int question_count;
        private int answer_timeout;
        private int max_players;
        public GetRoomStateResponse(int status, bool has_game_begun, string[] players, int question_count, int answer_timeout, int max_players)
        {
            this.status = status;
            this.has_game_begun = has_game_begun;
            this.players = players;
            this.question_count = question_count;
            this.answer_timeout = answer_timeout;
            this.max_players = max_players;
        }

        public int GetStatus()
        {
            return status;
        }

        public bool GetHasGameBegun()
        {
            return has_game_begun;
        }

        public string[] GetPlayers()
        {
            return players;
        }

        public int GetQuestionCount()
        {
            return question_count;
        }

        public int GetAnswerTimeout()
        {
            return answer_timeout;
        }

        public int GetMaxPlayers()
        {
            return max_players;
        }

    }
}
