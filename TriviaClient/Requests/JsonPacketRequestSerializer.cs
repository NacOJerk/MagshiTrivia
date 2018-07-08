using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using TriviaClient.Utils;


namespace TriviaClient.Requests
{
    class JsonPacketRequestSerializer
    {
        private static JsonPacketRequestSerializer _instance;

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
            string data = JsonConvert.SerializeObject(json);
            return Encapsule(data, id);
        }

        public byte[] Seriliaze(LoginRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.LOGIN_REQUEST);
        }

        public byte[] Seriliaze(SignupRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.SIGNUP_REQUEST);
        }

        public byte[] Seriliaze(GetPlayersInRoomRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.GET_PLAYERS_IN_ROOM_REQUEST);
        }

        public byte[] Seriliaze(JoinRoomRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.JOIN_ROOM_REQUEST);
        }

        public byte[] Seriliaze(CreateRoomRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.CREATE_ROOM_REQUEST);
        }

        public byte[] Seriliaze(SignoutRequest request)
        {
            return Encapsule("", RequestID.SIGNOUT_REQUEST);
        }

        public byte[] Seriliaze(GetRoomsRequest request)
        {
            return Encapsule("", RequestID.GET_ROOMS_REQUEST);
        }

        public byte[] Seriliaze(GetHighscoresRequest request)
        {
            return Encapsule("", RequestID.GET_HIGHSCORE);
        }

        public byte[] Seriliaze(LeaveRoomRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.LEAVE_ROOM_REQUEST);
        }

        public byte[] Seriliaze(CloseRoomRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.CLOSE_ROOM_REQUEST);
        }

        public byte[] Seriliaze(StartGameRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.START_GAME_REQUEST);
        }

        public byte[] Seriliaze(GetRoomStateRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.GET_ROOM_STATE_REQUEST);
        }

        public byte[] Seriliaze(GetStatsRequest request)
        {
            return Encapsule("", RequestID.GET_STATS_REQUEST);
        }

        public byte[] Seriliaze(SendAnswerRequest request)
        {
            return Encapsule(JsonConvert.SerializeObject(request), RequestID.SEND_ANSWER_REQUEST);
        }

        private JsonPacketRequestSerializer()
        {

        }

        public static JsonPacketRequestSerializer GetInstance()
        {
            if (_instance == null)
                _instance = new JsonPacketRequestSerializer();
            return _instance;
        }

    }
}
