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
	size_t size = hexstring.size() / 2;
	hexstringToBytes(hexstring, input);
	std::cout << "Input bytes: " << input.size() << '\n';

	size_t i = 0;
	for (auto& el : input)

		std::cout << "el " << ++i <<": " << (int)el << '\n';

	Bytes r1(size - 1); // If too big, will contain zero bytes!
	i = 0;
	for (auto& el : r1)
		std::cout << i++ << "r1: " << el << " ";
	std::cout << '\n';
	
	// Alternative: sha256(&input[0], size, r1);
	sha256(input.data(), size, r1);

	Bytes r2(20);
	ripemd160(&r1[0], r1.size(), r2);

	// Prepend the version byte
	r2.insert(std::begin(r2), 0x00);

	// Perform SHA256 twice and set checksum to the first four bytes of the result.
	Bytes r3(32);
	sha256(&r2[0], r2.size(), r3);
	sha256(&r3[0], r3.size(), r3);
	Bytes::const_iterator first = r3.begin();
	Bytes::const_iterator last = first + 4;

	// Append checksum to r2 (ripemd160 hash)
	r2.insert(r2.end(), first, last);
	
	for (auto& el : r2)
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)el;
	std::cout << '\n';
	
	std::string b58 = EncodeBase58(r2); 
	for (auto& el : b58)
		std::cout << el;
	std::cout << '\n';

	return 0;
}
