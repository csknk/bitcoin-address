#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include "utilities.h"


std::string sha256(const uint8_t preimageBytes[], size_t len)
{
	unsigned char res[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, preimageBytes, len);
	SHA256_Final(res, &sha256);
	std::stringstream ss;
	for (auto& el : res)
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)el;
	return ss.str();
}

int main()
{
	std::string hexstring;
	std::cout << "Enter a hexstring:\n";
	std::cin >> hexstring;

//	utilities::Bytes input;
	size_t size = hexstring.size() / 2;
	std::cout << "size: " << size << '\n';
	uint8_t input[size];
	utilities::hexstringToIntArray(hexstring, input);
//	for (auto& el : input)
//		std::cout << std::dec << (int)el << " ";
//	std::cout << '\n';
	std::cout << sha256(input, size) << '\n';

	utilities::Bytes b;
	utilities::hexstringToBytes("deadbeef", b);
	for (auto& el : b)
		std::cout << (int)el << " ";
	std::cout << '\n';
	size_t j = 4;
	std::cout << sha256(&b[0], j) << '\n';
	return 0;
}
