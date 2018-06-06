#include <Core/Core.h>
#include <Cypher/Snow2.h>

#include <Protect/Protect.h>

using namespace Upp;

One<Cypher> GetCypher(uint8_t const *nonce, int nonceSize)
{
	String key = ScanHexString("AABBCCDDEEFF00112233445566778899");
	One<Cypher> res = new Snow2((uint8_t const *)~key, key.GetCount(), nonce, nonceSize);
	return res;
}


void encrypted(int x)
{
	PROTECT_START_FUNC(GetCypher);

	Cerr() << "2 * X = " << 2 * x << "\n";

	PROTECT_END_FUNC;
}

void obfuscated(String const &s)
{
	OBFUSCATE_START_FUNC;

	Cerr() << "S is : " << s << "\n";

	OBFUSCATE_END_FUNC;
}

CONSOLE_APP_MAIN
{
	// check if protection key is ok; if not abort
	ON_PROTECT_BAD_KEY(GetCypher) {
		Cerr() << "Bad key, aborting\n";
		Exit(1);
	}

	// run an encripted function, twice
	encrypted(5);
	encrypted(10);
	
	// run an obfuscated function, twice
	obfuscated("Hello");
	obfuscated("Massimo");
	
	// this data will be encrypted and can be read by PROTECT_DECRYPT_DATA call
	const char *encryptedData = PROTECT_DATA_START "This data was encrypted\n" PROTECT_DATA_END;
	Cerr() << PROTECT_DECRYPT_DATA(GetCypher, encryptedData);
}
