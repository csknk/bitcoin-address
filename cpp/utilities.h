#ifndef UTILITIES_H
#define UTILITIES_H
#endif

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <typeinfo>

namespace utilities {

typedef std::vector<unsigned char> Bytes;

int hexDigitToInt(char digit)
{
	digit = tolower(digit);
	if (digit >= '0' && digit <='9')
	       return (int)(digit - '0');
	else if (digit >= 'a' && digit <= 'f') {
		return (int)(digit - '1' - '0') + 10; 
	}	
	return -1;
}

int hexstringToIntArray(std::string const& hexstring, uint8_t result[])
{
	if (hexstring.size() % 2) {
		std::cerr << "The hexstring is not an even number of characters.\n";
		exit(EXIT_FAILURE);
	}
	
	size_t resultLength = hexstring.size() / 2;
	size_t i = 0;
	for (auto it = hexstring.begin(); it != hexstring.end(); it = it + 2) {
		int sixteens = hexDigitToInt(*it);
		int units = hexDigitToInt(*std::next(it));
		result[i] = (sixteens << 4) | units;
		i++;
	}
	return resultLength;
}

int hexstringToBytes(std::string const& hexstring, Bytes& result)
{
	if (hexstring.size() % 2) {
		std::cerr << "The hexstring is not an even number of characters.\n";
		exit(EXIT_FAILURE);
	}
	
	size_t resultLength = hexstring.size() / 2;
	size_t i = 0;
	for (auto it = hexstring.begin(); it != hexstring.end(); it = it + 2) {
		int sixteens = hexDigitToInt(*it);
		int units = hexDigitToInt(*std::next(it));
		result.push_back((sixteens << 4) | units);
		i++;
	}
	return resultLength;
}
	
	
/**
 * Print a string as hexadecimal values.
 *
 * */ 
void printToHex(std::string s)
{
	std::cout << "printToHex() for " << s << ": ";
	for(size_t i = 0; i < s.size(); i++) {
		std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)s[i];
	}
	std::cout << '\n';
}

/**
 * Print a string as hexadecimal values using printf()
 *
 * */ 
void printToHexCStyle(std::string s)
{
	std::cout << "printToHex() for " << s << ": ";
	for(size_t i = 0; i < s.size(); i++) {
		printf("%02hhx", s[i]);
	}
	std::cout << '\n';
}

/**
 *
 * return a hex string representation of the value of an integer
 *
 * */ 
std::string intToHexString1(int num)
{
	std::stringstream ss;
	ss << std::hex << num;
	return ss.str();
}

/**
 * Convert an int to a hexadecimal string, using arithmetic.
 *
 * */
std::string intToHexString2(int num)
{
	const char hexChars[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	std::string result;
	while (num) {
		char tmp = hexChars[num % 16];
		result.insert(result.begin(), tmp);
		num /= 16;
	}
	return result;
}

/**
 * Build a hex string representation of bytes.
 * 
 * */
void charToHexString(const char& c, std::string& s)
{
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << std::hex << (0xff & (int)c);
	s.append(ss.str());
}

template <typename T>
void printHex(T input)
{
	for (auto& el : input)
		std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)el;
	std::cout << '\n';
}

} // utilities
