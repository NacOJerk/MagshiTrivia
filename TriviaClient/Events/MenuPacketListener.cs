using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.infrastructure;
using TriviaClient.Connections;
using TriviaClient.Responses;

namespace TriviaClient.Events
{
    class MenuPacketListener : IPacketListener
    {
        [PacketHandler(Utils.ResponseID.LOGOUT_RESPONSE)]
        public void Logout(PacketEvent e)
        {
            e.GetConnection().GetData().Logout();
            e.GetMainWindow().Dispatcher.BeginInvoke((Action)delegate ()
            {
                e.GetMainWindow().RewriteTextBlock(e.GetMainWindow().MenuUsername, "");
                e.GetMainWindow().SwitchWindow(e.GetMainWindow().LoginWindow);
            });
        }
    }
}
