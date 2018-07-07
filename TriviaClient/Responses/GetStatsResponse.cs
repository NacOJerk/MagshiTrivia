using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Responses
{
    class GetStatsResponse
    {
        float _winRate;
        float _successRate;
        float _stupidityRate;
        float _averageTime;

        public GetStatsResponse(float winRate, float successRate, float stupidityRate, float averageTime)
        {
            _winRate = winRate;
            _successRate = successRate;
            _stupidityRate = stupidityRate;
            _averageTime = averageTime;
        }

        public float GetWinRate()
        {
            return _winRate;
        }

        public float GetSuccessRate()
        {
            return _successRate;
        }

        public float GetStupidityRate()
        {
            return _stupidityRate;
        }

        public float GetAverageTime()
        {
            return _averageTime;
        }
    }
}
