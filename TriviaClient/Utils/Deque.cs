using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.Utils
{

    //I couldn't find the deque I wanted so I made my own one
    class Deque<E>
    {
        private class BiNode
        {
            private BiNode _f;
            private BiNode _b;
            private E _val;

            public BiNode(E val, BiNode b = null, BiNode f = null)
            {
                _val = val;
                _f = f;
                _b = b;
            }

            public void SetForward(BiNode f)
            {
                _f = f;
            }

            public void SetBackward(BiNode b)
            {
                _b = b;
            }

            public void SetValue(E val)
            {
                _val = val;
            }

            public E GetValue()
            {
                return _val;
            }

            public BiNode GetBackward()
            {
                return _b;
            }

            public BiNode GetForward()
            {
                return _f;
            }

            public bool HasBackward()
            {
                return _b != null;
            }

            public bool HasForward()
            {
                return _f != null;
            }




        }

        private BiNode _front;
        private BiNode _back;

        //O(1)
        public Deque()
        {
            _front = null;
            _back = null;
        }

        //O(1)
        public void AddFront(E val)
        {
            BiNode node = new BiNode(val);
            if(_front != _back || (_front == _back && _back != null))
            {
                node.SetForward(_front);
                _front.SetBackward(node);
                _front = node;
            }
            else if(_front == _back && _back == null)
            {
                _front = _back = node;
            }
        }

        //O(1)
        public void AddBackward(E val)
        {
            BiNode node = new BiNode(val);
            if (_front != _back || (_front == _back && _back != null))
            {
                node.SetBackward(_back);
                _back.SetForward(node);
                _back = node;
            }
            else if (_front == _back && _back == null)
            {
                _front = _back = node;
            }
        }

        //O(1)
        public E PopFront()
        {
            if (IsEmpty())
                throw new Exception("Deque is empty !");
            E val = _front.GetValue();

            if (_front == _back)
                _front = _back = null;
            else
            {
                _front = _front.GetForward();
                _front.SetBackward(null);
            }
            return val;
        }

        //O(1)
        public E PopBack()
        {
            if (IsEmpty())
                throw new Exception("Deque is empty !");
            E val = _back.GetValue();

            if (_front == _back)
                _front = _back = null;
            else
            {
                _back = _front.GetBackward();
                _back.SetForward(null);
            }
            return val;
        }

        //O(1)
        public E PeekFront()
        {
            return _front.GetValue();
        }

        //O(1)
        public E PeekBack()
        {
            return _back.GetValue();
        }

        //O(1)
        public bool IsEmpty()
        {
            return _back == _front && _front == null;
        }

    }
}
