using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using TriviaClient.Utils;


namespace TriviaClient.Requests
{
    class JsonPackerRequestSerializer
    {
        private static JsonPackerRequestSerializer _instance;

        private byte[] Encapsule(string data, RequestID id)
        {
            byte[] buff = new byte[data.Length + 5];
            buff[0] = (byte) id;
            buff[1] = (byte)(data.Length >> 24 & 255);
            buff[2] = (byte)(data.Length >> 16 & 255);
            buff[3] = (byte)(data.Length >> 8 & 255);
            buff[4] = (byte)(data.Length & 255);
            for (int i = 0; i < data.Length; buff[i + 5] = (byte) data[i], i++);
            return buff;
        }

        private byte[] GetBuff(dynamic json, RequestID id)
        {
            return Encapsule(JsonConvert.SerializeObject(json), id);
        }

        public byte[] Seriliaze(LoginRequest request)
        {
            JsonObjec
        }

        private JsonPackerRequestSerializer()
        {

        }

        public static JsonPackerRequestSerializer GetInstance()
        {
            if (_instance == null)
                _instance = new JsonPackerRequestSerializer();
            return _instance;
        }

    }
}
