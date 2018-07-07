using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.infrastructure
{
    class UserData
    {
        private string username;
        private int roomId;

        public UserData()
        {
            username = "";
            roomId = -1;
        }

        public bool IsLoggedIn()
        {
            return username.Length > 0;
        }

        public bool IsInRoom()
        {
            return roomId > -1;
        }

        public void Login(string username)
        {
            if (username.Length <= 0)
                throw new Exception("Username can not be empty");
            if (IsLoggedIn())
                throw new Exception("You must logout first");
            this.username = username;
        }

        public string GetUsername()
        {
            if (!IsLoggedIn())
                throw new Exception("The user haven't connected yet");
            return username;
        }

        public void Logout()
        {
            username = "";
        }

        public void EnterRoom(int id)
        {
            this.roomId = id;
        }

        public int GetRoomId()
        {
            return roomId;
        }

        public void LeaveRoom()
        {
            roomId = -1;
        }
    }
}
