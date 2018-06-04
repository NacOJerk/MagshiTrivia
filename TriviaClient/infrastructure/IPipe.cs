using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.infrastructure
{
    interface IPipe
    {
        byte[] Read(byte[] buff);
        byte[] Write(byte[] buff);
    }
}
