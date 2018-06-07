using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TriviaClient.Utils;

namespace TriviaClient.Events
{
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = false, Inherited = false)]
    class PacketHandler : Attribute
    {
        private ResponseID id;

        public PacketHandler(ResponseID id)
        {
            this.id = id;
        }

        public ResponseID GetID()
        {
            return id;
        }

    }
}
