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
            return System.Text.Encoding.UTF8.GetString(buff);
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

        public CreateRoomResponse DeserializeCreateRoomResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<CreateRoomResponse>(Decapsule(buff));
        }

        public GetRoomsResponse DeserializeGetRoomsResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<GetRoomsResponse>(Decapsule(buff));
        }
        
        public JoinRoomResponse DeserializeJoinRoomResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<JoinRoomResponse>(Decapsule(buff));
        }

        public GetRoomStateResponse DeserializeGetRoomStateResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<GetRoomStateResponse>(Decapsule(buff));
        }

        public LeaveRoomResponse DeserializeLeaveRoomResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<LeaveRoomResponse>(Decapsule(buff));
        }

        public StartGameResponse DeserializeStartGameResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<StartGameResponse>(Decapsule(buff));
        }

        public GetHighscoresResponse DeserializeGetHighscoresResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<GetHighscoresResponse>(Decapsule(buff));
        }

        public GetStatsResponse DeserializeGetStatsResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<GetStatsResponse>(Decapsule(buff));
        }

        public SendResultsResponse DeserializeSendResultsResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<SendResultsResponse>(Decapsule(buff));
        }

        public SendQuestionResponse DeserializeSendQuestionResponse(byte[] buff)
        {
            return JsonConvert.DeserializeObject<SendQuestionResponse>(Decapsule(buff));
        }
    }
}
