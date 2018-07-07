#pragma once

#include "consts.hpp"
#include <vector>
#include <ostream>
#include <deque>

//Everything is going to be inside here , ewww right ?
namespace RSA
{

	typedef unsigned long long integer;

	namespace hide
	{
		integer readVarInteger(std::deque<byte>& buff)
		{
			int numRead = 0;
			integer result = 0;
			byte read = 0;
			do
			{
				read = buff.front();
				buff.pop_front();
				byte value = read & 0b01111111;
				result |= (value << (7 * numRead));
				numRead++;
				if (numRead > 10)
				{
					throw std::exception("Var long is too long");
				}
			} while ((read & 0b10000000));
			return result;
		}
		void writeVarInteger(buffer& buff, integer write)
		{
			do
			{
				byte temp = (byte)write & 0b01111111;
				write >>= 7;
				if (write != 0)
				{
					temp |= 0b10000000;
				}
				buff.push_back(temp);
			} while (write != 0);
		}
	}

	class Primes
	{
		std::vector<integer> _primes;
	public:
		void buildPrimes(size_t max)
		{
			std::vector<integer> vector(max);
			for (integer i = 0; i < max; vector[i] = i + 1, i++);
			for (integer i = 1; i < max; i++)
			{
				if (vector[i] != 0)
				{
					const integer prime = i + 1;
					_primes.push_back(prime);
					for (integer j = i + prime; j < max; j += prime)
					{
						vector[j] = 0;
					}
				}
			}
		}
		std::pair<integer, integer> getTwoPrimes()
		{
			const unsigned int min = 0, max = _primes.size();
			return std::make_pair(_primes[min + rand() % ((max + 1) - min)], _primes[min + rand() % ((max + 1) - min)]);
		}
		size_t getPrimeAmount()
		{
			return _primes.size();
		}
	};
	//There is no public / private key cus of the way Im gonna implemenet it in the server
	class Key
	{
		integer _key;
		integer _base;
	public:
		Key(const integer& key, const integer& base) : _key(key), _base(base) {}
		Key(buffer buff)
		{
			std::deque<byte> buf;
			std::copy(buff.begin(), buff.end(), std::back_inserter(buf));
			_key = hide::readVarInteger(buf);
			_base = hide::readVarInteger(buf);
		}
		integer getKey() const { return _key; }
		integer getBase() const { return _base; }
		buffer getBuffer() const
		{
			//first key than base
			buffer buff;
			hide::writeVarInteger(buff, _key);
			hide::writeVarInteger(buff, _base);
			return buff;
		}
		friend std::ostream& operator<<(std::ostream &os, const Key &dt)
		{
			os << dt.getKey() << " " << dt.getBase();
			return os;
		}
	};
	namespace hide
	{
		integer GCD(integer u, integer v) {
			while (v != 0) {
				integer r = u % v;
				u = v;
				v = r;
			}
			return u;
		}
		integer getCoPrime(integer low, integer up, const integer& phi)
		{
			if (phi < up)
				up = phi - 1;
			while (true)
			{
				integer test = low + rand() % ((up + 1) - low);
				if (GCD(test, phi) == 1)
					return test;
			}
		}
		integer getPrivateKey(integer e, integer phi)
		{
			e = e%phi;
			for (integer x = 1; x<phi; x++)
				if ((e*x) % phi == 1)
					return x;
			return -1;
		}
		template <typename T>
		T modpow(T a, T b, T n) {//Copied this one
			integer x = 1, y = a;
			while (b > 0) {
				if (b % 2 == 1) {
					x = (x*y) % n; // multiplying with base
				}
				y = (y*y) % n; // squaring the base
				b /= 2;
			}
			return x % n;
		}

		integer popBuff(std::deque<byte>& buff)
		{
			integer res = buff.front();
			buff.pop_front();
			return res;
		}
		buffer crypt(buffer buff, Key key, bool encrypt)
		{
			std::deque<byte> buf;
			std::copy(buff.begin(), buff.end(), std::back_inserter(buf));
			buffer res;
			while (!buf.empty())
			{
				integer source = encrypt ? popBuff(buf) : readVarInteger(buf);
				integer result = modpow<integer>(source, key.getKey(), key.getBase());
				if (encrypt)
				{
					writeVarInteger(res, result);
				}
				else
				{
					res.push_back((byte)result);
				}
			}
			return res;
		}
	}

	//first key is the one with the bigger key (the one you should send out)
	std::pair<Key, Key> generateKeys(integer prime1, integer prime2, integer lowLimit, integer upLimit)
	{
		//We calc our base
		integer N = prime1 * prime2;
		integer phi = (prime1 - 1) * (prime2 - 1);//We calc phi
		integer e = hide::getCoPrime(lowLimit, upLimit, phi);
		integer d = hide::getPrivateKey(e, phi);
		if (e < d)
			std::swap(e, d);
		return std::make_pair(Key(e, N), Key(d, N));
	}
	buffer encrypt(buffer buff, Key key)
	{
		return hide::crypt(buff, key, true);
	}
	buffer decrypt(buffer buff, Key key)
	{
		return hide::crypt(buff, key, false);
	}
};