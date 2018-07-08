using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Responses
{
    class GetHighscoresResponse
    {
        public string scores { get; set; }
        public int status { get; set; }

        public Dictionary<string, string>[] GetHighscores()
        {
            string[] highs = scores.Split('\n');
            Dictionary<string, string>[] _highscores = new Dictionary<string, string>[highs.Length - 1];
            for(int i = 0; i < _highscores.Length; i++)
            {
                _highscores[i] = new Dictionary<string, string>();
                string[] fields = highs[i].Split('\r');
                _highscores[i]["name"] = fields[0];
                _highscores[i]["score"] = fields[1];
            }
            return _highscores;
        }

        public int GetStatus()
        {
            return status;
        }
    }
}
