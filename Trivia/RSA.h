#pragma once

#include "consts.hpp"
#include <vector>
#include <ostream>
#include <deque>

//Everything is going to be inside here , ewww right ?
namespace RSA
{

	typedef unsigned long long integer;

	class Primes
	{
		std::vector<integer> _primes;
	public:
		void buildPrimes(size_t max);
		std::pair<integer, integer> getTwoPrimes();
		size_t getPrimeAmount();
	};
	//There is no public / private key cus of the way Im gonna implemenet it in the server
	class Key
	{
		integer _key;
		integer _base;
	public:
		Key(const integer& key, const integer& base);
		Key(buffer buff);
		integer getKey() const;
		integer getBase() const;
		buffer getBuffer() const;
		friend std::ostream& operator<<(std::ostream &os, const Key &dt);
	};
	namespace hide
	{
		integer readVarInteger(std::deque<byte>& buff);
		void writeVarInteger(buffer& buff, integer write);
		integer GCD(integer u, integer v);
		integer getCoPrime(integer low, integer up, const integer& phi);
		integer getPrivateKey(integer e, integer phi);
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
		integer popBuff(std::deque<byte>& buff);

		buffer crypt(buffer buff, Key key, bool encrypt);
	}

	//first key is the one with the bigger key (the one you should send out)
	std::pair<Key, Key> generateKeys(integer prime1, integer prime2, integer lowLimit, integer upLimit);

	buffer encrypt(buffer buff, Key key);

	buffer decrypt(buffer buff, Key key);
};