#include <math.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <assert.h>


std::string EncodeBase58(const unsigned char* pbegin, const unsigned char* pend);
std::string EncodeBase58(const std::vector<unsigned char>& inputBuffer);
