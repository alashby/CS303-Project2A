// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#pragma once
#include <stdexcept>
using namespace std;

class Expression_Error : public invalid_argument {
public:
	Expression_Error(string msg) : invalid_argument(msg) {}
};