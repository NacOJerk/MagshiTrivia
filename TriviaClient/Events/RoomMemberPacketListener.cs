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
            Console.WriteLine("O hey there ?");
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate () {
                e.GetMainWindow().FillRoomMemberData(resp);
            });
        }

        private void ResetRoomWindow(PacketEvent e)
        {
            Console.WriteLine("who the fuck invoked me ?");
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {

                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MemberQuestionCount, "[questionCount] questions in this room");
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MemberAnswerTimeout, "Only [answerTimeout] seconds to answer");
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MemberConnectedPlayers, "[players]/[maxPlayers] players in the room");
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().RoomMemberName, "Username's");
            });
        }

        [PacketHandler(Utils.ResponseID.LEAVE_ROOM_RESPONSE)]
        public void LeaveRoom(PacketEvent e)
        {
            e.GetConnection().GetData().LeaveRoom();
            e.GetConnection().SetListener(new MenuPacketListener());
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                ResetRoomWindow(e);
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().MenuWindow);
            });
        }

        [PacketHandler(Utils.ResponseID.START_GAME_RESPONSE)]
        public void StartGame(PacketEvent e)
        {
            e.GetConnection().GetData().LeaveRoom();
            e.GetConnection().SetListener(new GamePacketListener());
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                ResetRoomWindow(e);
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().LoadingMessage, "Starting game");
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoadingWindow);
            });
        }

        [PacketHandler(Utils.ResponseID.LOGOUT_RESPONSE)]
        public void Logout(PacketEvent e)
        {
            ResetRoomWindow(e);
            e.GetConnection().GetData().LeaveRoom();
            e.GetConnection().GetData().Logout();
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MenuUsername, "");
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoginWindow);
            });
        }
    }
}
