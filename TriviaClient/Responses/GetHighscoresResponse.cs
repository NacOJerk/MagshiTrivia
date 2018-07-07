using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace TriviaClient.Responses
{
    class GetHighscoresResponse
    {
        private Dictionary<string, string>[] _highscores;
        private int _status;

        public GetHighscoresResponse(int status, Dictionary<string, string>[] highscores)
        {
            _status = status;
            _highscores = highscores;
        }

        public Dictionary<string, string>[] GetHighscores()
        {
            return _highscores;
        }

        public int GetStatus()
        {
            return _status;
        }
    }
}
