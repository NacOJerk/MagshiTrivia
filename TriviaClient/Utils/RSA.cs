using System.Collections.Generic;
using System;

namespace RSA
{
    class Primes
    {
        private List<ulong> primes;

        public Primes()
        {
            primes = new List<ulong>();
        }

        public void BuildPrimes(uint max)
        {
            List<uint> vec = new List<uint>();
            for (uint i = 0; i < max; vec.Add(i + 1), i++);
            for (int i = 1; i < max; i++)
            {
                if(vec[i] != 0)
                {
                    int prime = i + 1;
                    primes.Add((ulong)prime);
                    for (int j = i + prime; j < max; j += prime)
                    {
                        vec[j] = 0;
                    }
                }
            }
        }
        public Tuple<ulong, ulong> GetTwoPrimes()
        {
            Random rnd = new Random();
            int first = rnd.Next(0, primes.Count);
            int second = 0;
            do
            {
                second = rnd.Next(0, primes.Count);
            } while (second == first);
            return Tuple.Create(primes[first], primes[second]);
        }
    }

    class Key
    {
        private ulong _key;
        private ulong _base;

        public Key(ulong key, ulong bas)
        {
            _key = key;
            _base = bas;
        }

        public Key(List<byte> buff)
        {
            _key = Hide.ReadVarInteger(buff);
            _base = Hide.ReadVarInteger(buff);
        }

        public ulong GetKey()
        {
            return _key;
        }

        public ulong GetBase()
        {
            return _base;
        }

        public List<byte> GetBuffer()
        {
            List<byte> buff = new List<byte>();
            Hide.WriteVarInteger(buff, _key);
            Hide.WriteVarInteger(buff, _base);
            return buff;
        }

    }

    static class Hide
    {
        public static ulong ReadVarInteger(List<byte> buff)
        {
            int numRead = 0;
            ulong result = 0;
            byte read = 0;
            do
            {
                read = buff[0];
                buff.RemoveAt(0);
                byte value = (byte)( read & 0b01111111);
                result |= ((ulong)value << (7 * numRead));
                numRead++;
                if (numRead > 10)
                {
                    throw new Exception("Var long is too long");
                }
            } while ((read & 0b10000000) != 0);
            return result;
        }
        public static void WriteVarInteger(List<byte> buff, ulong write)
        {
            do
            {
                byte temp = (byte) (write & 0b01111111);
                write >>= 7;
                if (write != 0)
                {
                    temp |= 0b10000000;
                }
                buff.Add(temp);
            } while (write != 0);
        }
        public static ulong GCD(ulong u, ulong v)
        {
            while (v != 0)
            {
                ulong r = u % v;
                u = v;
                v = r;
            }
            return u;
        }
        public static ulong GetCoPrime(ulong low, ulong up, ulong phi)
		{
            Random rnd = new Random();
            if (phi<up)
                up = phi - 1;
			while (true)
			{
                ulong test = (ulong) rnd.Next((int)low, (int)up + 1);
				if (GCD(test, phi) == 1)
					return test;
			}
}
        public static ulong GetPrivateKey(ulong e, ulong phi)
		{
			e = e%phi;
			for (ulong x = 1; x<phi; x++)
				if ((e*x) % phi == 1)
					return x;
			return 0;
		}
        public static ulong Modpow(ulong a, ulong b, ulong n)
        {//Copied this one
            ulong x = 1, y = a;
            while (b > 0)
            {
                if (b % 2 == 1)
                {
                    x = (x * y) % n; // multiplying with base
                }
                y = (y * y) % n; // squaring the base
                b /= 2;
            }
            return x % n;
        }
        public static ulong PopBuff(List<byte> buff)
        {
            ulong res = buff[0];
            buff.RemoveAt(0);
            return res;
        }
        public static List<byte> Crypt(List<byte> buff, Key key, bool encrypt)
        {
            List<byte> res = new List<byte>();
            Console.WriteLine("The buff length is " + buff.Count);
            while (buff.Count > 0)
            {
                ulong source = encrypt ? PopBuff(buff) : ReadVarInteger(buff);
                ulong result = Modpow(source, key.GetKey(), key.GetBase());
                if (encrypt)
                {
                    WriteVarInteger(res, result);
                }
                else
                {
                    res.Add((byte)result);
                }
            }
            return res;
        }
    }

    static class RSA
    {
        public static Tuple<Key, Key> GenerateKeys(ulong prime1, ulong prime2, ulong lowerBound, ulong upperBound)
        {
            ulong N = prime1 * prime2;
            ulong phi = (prime1 - 1) * (prime2 - 1);
            ulong e = Hide.GetCoPrime(lowerBound, upperBound, phi);
            ulong d = Hide.GetPrivateKey(e, phi);
            if(e < d)
            {
                ulong temp = e;
                e = d;
                d = temp;
            }
            return Tuple.Create(new Key(e, N), new Key(d, N));
        }
        public static List<byte> Encrypt(List<byte> buff, Key k)
        {
            return Hide.Crypt(buff, k, true);
        }
        public static List<byte> Decrypt(List<byte> buff, Key k)
        {
            return Hide.Crypt(buff, k, false);
        }
    }

}