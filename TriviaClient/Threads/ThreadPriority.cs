using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using TriviaClient.Utils;


namespace TriviaClient.Threads
{
    class ThreadPriority
    {
        public readonly object Lock = new object();
        private readonly object DequeLock = new object();
        private Deque<int> _threads;

        public ThreadPriority()
        {
            _threads = new Deque<int>();
        }

        private void Wait()
        {
            do
            {
                Monitor.Wait(Lock);
            } while (!IsFirst());
            lock (DequeLock)
            {
                if (_threads.PopFront() != Thread.CurrentThread.ManagedThreadId)
                    throw new Exception("Some thing went horribly wrong !");
            }
        }

        public void PulseAll()
        {
            Monitor.PulseAll(Lock);
        }

        private bool IsFirst()
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            lock(DequeLock)
            {
                return _threads.PeekFront() == id;
            }
        }

        public void WaitFirst()
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            lock (DequeLock)
            {
                _threads.AddFront(id);
            }
            Wait();
        }
        
        public void WaitLast()
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            lock (DequeLock)
            {
                _threads.AddBackward(id);
            }
            Wait();

        }

    }
}
