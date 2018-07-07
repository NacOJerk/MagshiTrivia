#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include "RSA.h"
#include <iostream>
#include <time.h>

#define PRIME_MAX 10'000
#define E_MIN 100
#define E_MAX 500

using RSA::Primes;
using RSA::Key;
using RSA::integer;

void main()
{
	std::srand(time(0));
	std::cout << "Generating keys..." << std::endl;
	Primes primes;
	primes.buildPrimes(PRIME_MAX);
	std::pair<integer, integer> twoPrimes = primes.getTwoPrimes();
	std::pair<Key, Key> keys = RSA::generateKeys(twoPrimes.first, twoPrimes.second, E_MIN, E_MAX);
	std::cout << "Done generating keys " << std::endl << std::endl;

	std::cout << "Starting server...." << std::endl;
	try
	{
		WSAInitializer wsaInit;
		Server myServer(keys);

		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
}