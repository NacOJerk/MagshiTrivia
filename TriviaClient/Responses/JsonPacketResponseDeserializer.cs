using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient.Responses
{
    class JsonPacketResponseDeserializer
    {
        private static JsonPacketResponseDeserializer _instance = null;

        private JsonPacketResponseDeserializer() { }

        public static JsonPacketResponseDeserializer GetInstance()
        {
            if(_instance == null)
            {
                _instance = new JsonPacketResponseDeserializer();
            }
            return _instance;
        }

        private string Decapsule(byte[] buff)
        {
            return BitConverter.ToString(buff);
        }

        public ErrorResponse DeserializeErrorResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<ErrorResponse>(Decapsule(buff));
        }

        public LoginResponse DeserializeLoginResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<LoginResponse>(Decapsule(buff));
        }

        public SignupResponse DeserializeSignupResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<SignupResponse>(Decapsule(buff));
        }

        public LogoutResponse DeserializeLogoutResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<LogoutResponse>(Decapsule(buff));
        }

        public GetPlayersInRoomResponse DeserializeGetPlayersInRoomResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(Decapsule(buff));
        }
    }
}
