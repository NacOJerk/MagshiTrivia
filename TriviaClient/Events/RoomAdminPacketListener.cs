using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Responses;

namespace TriviaClient.Events
{
    class RoomAdminPacketListener : IPacketListener
    {
        [PacketHandler(Utils.ResponseID.GET_PLAYERS_IN_ROOM_RESPONSE)]
        public void UpdatePlayers(PacketEvent e)
        {
            GetPlayersInRoomResponse resp = JsonPacketResponseDeserializer.GetInstance().DeserializeGetPlayersInRoomResponse(e.GetResponse().GetBuffer());
            string people = e.GetMainWindow().AdminConnectedPlayers.Text;
            people = resp.GetPlayers().Length + people.Substring(people.IndexOf('/'));
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().AdminConnectedPlayers, people);
        }

        [PacketHandler(Utils.ResponseID.LOGOUT_RESPONSE)]
        public void Logout(PacketEvent e)
        {
            e.GetConnection().GetData().LeaveRoom();
            e.GetConnection().GetData().Logout();
            e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MenuUsername, "");
            e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoginWindow);
        }
    }
}
