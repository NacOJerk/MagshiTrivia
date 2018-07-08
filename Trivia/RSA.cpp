#include "RSA.h"

namespace RSA
{

	void Primes::buildPrimes(size_t max)
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

	std::pair<integer, integer> Primes::getTwoPrimes()
	{
		const unsigned int min = 0, max = _primes.size();
		return std::make_pair(_primes[min + rand() % ((max + 1) - min)], _primes[min + rand() % ((max + 1) - min)]);
	}

	size_t Primes::getPrimeAmount()
	{
		return _primes.size();
	}

	Key::Key(const integer& key, const integer& base) : _key(key), _base(base) {}

	Key::Key(buffer buff)
	{
		std::deque<byte> buf;
		std::copy(buff.begin(), buff.end(), std::back_inserter(buf));
		_key = hide::readVarInteger(buf);
		_base = hide::readVarInteger(buf);
	}

	integer Key::getKey() const { return _key; }

	integer Key::getBase() const { return _base; }

	buffer Key::getBuffer() const
	{
		//first key than base
		buffer buff;
		hide::writeVarInteger(buff, _key);
		hide::writeVarInteger(buff, _base);
		return buff;
	}

	std::ostream& operator<<(std::ostream &os, const Key &dt)
	{
		os << dt.getKey() << " " << dt.getBase();
		return os;
	}

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

		integer GCD(integer u, integer v)
		{
			while (v != 0) {
				integer r = u % v;
				u = v;
				v = r;
			}
			return u;
		}

		std::pair<integer, std::pair<integer, integer> > extendedEuclid(integer a, integer b) {
			if (a == 0) return std::make_pair(b, std::make_pair(0, 1));
			std::pair<integer, std::pair<integer, integer> > p;
			p = extendedEuclid(b % a, a);
			return std::make_pair(p.first, std::make_pair(p.second.second - p.second.first*(b / a), p.second.first));
		}

		integer getPrivateKey(integer e, integer phi)
		{
			return (extendedEuclid(e, phi).second.first + phi) % phi;
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

}