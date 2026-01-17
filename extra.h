#ifndef EXTRA_H
#define EXTRA_H

#include "class.h"
#include <string>

bool validInput(std::string number1);
LargeNum myArctan(LargeNum x);
LargeNum myExp(LargeNum x);
bool isPrime(LargeNum number);
std::string toStr(const LargeNum& number);
LargeNum convert(std::string num);
std::string doubleToString(double d);
LargeNum myExp(LargeNum x);

#endif