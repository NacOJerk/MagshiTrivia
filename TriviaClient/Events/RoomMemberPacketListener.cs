using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Responses;

namespace TriviaClient.Events
{
    class RoomMemberPacketListener : IPacketListener
    {
        [PacketHandler(Utils.ResponseID.GET_PLAYERS_IN_ROOM_RESPONSE)]
        public void UpdatePlayers(PacketEvent e)
        {
            GetPlayersInRoomResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeGetPlayersInRoomResponse(e.GetResponse().GetBuffer());
            string people = e.GetMainWindow().MemberConnectedPlayers.Text;
            people = resp.GetPlayers().Length + people.Substring(people.IndexOf('/'));
            e.GetMainWindow().MemberConnectedPlayers.Text = people;
        }

        [PacketHandler(Utils.ResponseID.LEAVE_ROOM_RESPONSE)]
        public void LeaveRoom(PacketEvent e)
        {
            e.GetConnection().getData().LeaveRoom();
            e.GetConnection().SetListener(new MenuPacketListener());
            e.GetMainWindow().MemberQuestionCount.Text = "[questionCount] questions in this room";
            e.GetMainWindow().MemberAnswerTimeout.Text = "Only [answerTimeout] seconds to answer";
            e.GetMainWindow().MemberConnectedPlayers.Text = "[players]/[maxPlayers] players in the room";
            e.GetMainWindow().RoomMemberName.Text = "Username's";
            e.GetMainWindow().SwitchWindow(e.GetMainWindow().MenuWindow);
        }

        [PacketHandler(Utils.ResponseID.LOGOUT_RESPONSE)]
        public void Logout(PacketEvent e)
        {
            e.GetConnection().getData().LeaveRoom();
            e.GetConnection().getData().Logout();
            e.GetMainWindow().MenuUsername.Text = "";
            e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoginWindow);
        }
    }
}
