#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include "utilities.h"
#include "base58.h"

using namespace utilities;
/**
 *
 * The signature of `SHA256_Update()` is:
 * `int SHA256_Update(SHA256_CTX *c, const void *data, size_t len);`
 * Note that 2nd parameter is a `const void *`. This means that the
 * caller must provide a pointer to data rather than a std::vector or a
 * vector iterator. The caller can either pass `v.data()` or `&v[0]`.
 *
 * */
int sha256(const uint8_t preimageBytes[], size_t len, Bytes& res)
{
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, preimageBytes, len); 
	int ret = SHA256_Final(&res[0], &sha256);
	return ret;
}

/**
 * Again note that RIPEMD160_Update receives a pointer to data.
 * */
int ripemd160(const uint8_t preimageBytes[], size_t len, Bytes& res)
{
	RIPEMD160_CTX ripemd160;
	RIPEMD160_Init(&ripemd160);
	RIPEMD160_Update(&ripemd160, preimageBytes, len);
	int ret = RIPEMD160_Final(&res[0], &ripemd160);
	return ret;
}

int main()
{
	std::string hexstring;
	std::cout << "Enter a hexstring representation of a public key:\n";
	std::cin >> hexstring;
	Bytes input;
	hexstringToBytes(hexstring, input);

	// If too big, will contain zero bytes that will get hashed!
	Bytes initialSHA256(SHA256_DIGEST_LENGTH);
	
	// Alternative: sha256(&input[0], size, initialSHA256);
	sha256(input.data(), input.size(), initialSHA256);

	Bytes ripemd160Hash(RIPEMD160_DIGEST_LENGTH);
	ripemd160(&initialSHA256[0], initialSHA256.size(), ripemd160Hash);
	printHex(ripemd160Hash);

	// Prepend the version byte
	ripemd160Hash.insert(std::begin(ripemd160Hash), 0x00);

	// Perform SHA256 twice  - checksum is the first four bytes of the result.
	Bytes checksumHash(SHA256_DIGEST_LENGTH);
	sha256(&ripemd160Hash[0], ripemd160Hash.size(), checksumHash);
	printHex(checksumHash);
	sha256(&checksumHash[0], checksumHash.size(), checksumHash);
	printHex(checksumHash);
	Bytes::const_iterator first = checksumHash.begin();
	Bytes::const_iterator last = first + 4;

	// Append checksum to ripemd160Hash
	ripemd160Hash.insert(ripemd160Hash.end(), first, last);
	printHex(ripemd160Hash);
	
	std::string b58 = EncodeBase58(ripemd160Hash); 
	std::cout << b58 << '\n';

	return 0;
}
