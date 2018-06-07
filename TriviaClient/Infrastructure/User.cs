using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Infrastructure
{
    class User
    {
        bool logged;

        private static User instance = null;

        public static User GetInstance()
        {
            if (instance == null)
                instance = new User();
            return instance;
        }

        private User()
        {

        }

    }
}
