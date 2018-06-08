using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Connections;
using TriviaClient.infrastructure;

namespace TriviaClient.Events
{
    class PacketEvent
    {
        private Connection conn;
        private Response resp;
        private MainWindow window;

        public PacketEvent(Connection conn , Response resp, MainWindow window)
        {
            this.conn = conn;
            this.resp = resp;
            this.window = window;
        }

        public Connection GetConnection()
        {
            return conn;
        }
        
        public Response GetResponse()
        {
            return resp;
        }

        public MainWindow GetMainWindow()
        {
            return window;
        }

    }
}
