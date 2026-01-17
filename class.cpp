#include<iostream>
#include<vector>
#include<string>
#include<limits>

#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

#include "class.h"
#include "extra.h"

#define PRECISION 115

void LargeNum::setVec(vector<char> vector){
    numVec = vector;
}

void LargeNum::setNegative(bool negativity){
    negative = negativity;
}

void LargeNum::setDotPos(int dotPosition){
    dotPos = dotPosition;
}

vector<char> LargeNum::getVec()const{
    return numVec;
}

bool LargeNum::isNegative()const{
    return negative;
}

int LargeNum::getDotPos()const{
    return dotPos;
}

int LargeNum::getSize(){
    return numVec.size();
}

LargeNum LargeNum::roundToPrecision(int precision) const {
    LargeNum result = *this; 
    int decimalPlaces = result.numVec.size() - result.dotPos;

    if (decimalPlaces <= precision) return result;

    if(precision == 0){
        for(int i = dotPos; i < result.numVec.size(); ++i){
            result.numVec[i] = '0';
        }
        return result;
    }

    int roundIndex = result.dotPos + precision;
    bool roundUp = (result.numVec[roundIndex] >= '5');

    result.numVec.erase(result.numVec.begin() + roundIndex, result.numVec.end());

    if (roundUp) {
        int i = roundIndex - 1;
        while (i >= 0) {
            if (result.numVec[i] == '.') {  
                --i;
            }
            if (result.numVec[i] < '9') {
                result.numVec[i] += 1;
                break;
            } else {
                result.numVec[i] = '0';
            }
            --i;
        }

        if (i < 0) {
            result.numVec.insert(result.numVec.begin(), '1');
            ++result.dotPos;
        }
    }

    while (result.numVec.size() > result.dotPos + 1 && result.numVec.back() == '0') {
        result.numVec.pop_back();
    }

    return result;
}

void LargeNum::copy(const LargeNum& number){
    numVec = number.numVec;
    negative = number.negative;
    dotPos = number.dotPos;
}

bool printCode = false;

bool LargeNum::equal(const LargeNum& number2) {
    if (negative != number2.negative){
        return false;
    }

    if(dotPos != number2.dotPos){
        return false;
    }

    int length1 = numVec.size();
    int length2 = number2.numVec.size();

    if(length1 != length2){
        return false;
    }


    for (int i = 0; i < min(length1, length2); ++i) {
        if (numVec[i] != number2.numVec[i]){
            return false;
        }
    }

    return true;
}

bool LargeNum::notEqual(const LargeNum& number2){
    return !equal(number2);
}

bool LargeNum::greater(const LargeNum& number2) {
    if (negative && !number2.negative) return false; 
    if (!negative && number2.negative) return true; 

    bool areNegative = negative && number2.negative;

    if (dotPos != number2.dotPos) {
        return (dotPos > number2.dotPos) ^ areNegative;
    }

    int len1 = numVec.size();
    int len2 = number2.numVec.size();
    int maxLen = (len1 > len2) ? len1 : len2;

    for (int i = 0; i < maxLen; ++i) {
        int digit1 = (i < len1) ? numVec[i] - '0' : 0;
        int digit2 = (i < len2) ? number2.numVec[i] - '0' : 0;

        if (digit1 != digit2) {
            return (digit1 > digit2) ^ areNegative;
        }
    }

    int frac1Len = len1 - dotPos - 1;
    int frac2Len = len2 - number2.dotPos - 1;
    int maxFracLen = (frac1Len > frac2Len) ? frac1Len : frac2Len;

    for (int i = 0; i < maxFracLen; ++i) {
        int frac1 = (i < frac1Len) ? numVec[dotPos + i + 1] - '0' : 0;
        int frac2 = (i < frac2Len) ? number2.numVec[number2.dotPos + i + 1] - '0' : 0;

        if (frac1 != frac2) {
            return (frac1 > frac2) ^ areNegative;
        }
    }

    return false;
}

bool LargeNum::less(const LargeNum& number2) const{
    if (negative && !number2.negative) return true;
    if (!negative && number2.negative) return false;

    bool areNegative = negative && number2.negative;

    int dotPos1 = dotPos;
    int dotPos2 = number2.dotPos;

    if (dotPos1 != dotPos2) {
        return (dotPos1 < dotPos2) ^ areNegative;
    }

    int len1 = numVec.size();
    int len2 = number2.numVec.size();
    
    int maxLen = (len1 > len2) ? len1 : len2;
    for (int i = 0; i < maxLen; ++i) {
        int digit1 = (i < len1) ? numVec[i] : 0;
        int digit2 = (i < len2) ? number2.numVec[i] : 0;
        if (digit1 != digit2) {
            return (digit1 < digit2) ^ areNegative;
        }
    }

    int frac1Len = len1 - dotPos1 - 1;
    int frac2Len = len2 - dotPos2 - 1;

    int maxFracLen = (frac1Len > frac2Len) ? frac1Len : frac2Len;
    for (int i = 0; i < maxFracLen; ++i) {
        int frac1 = (i < frac1Len) ? numVec[dotPos1 + i + 1] : 0;
        int frac2 = (i < frac2Len) ? number2.numVec[dotPos2 + i + 1] : 0;
        if (frac1 != frac2) {
            return (frac1 < frac2) ^ areNegative;
        }
    }

    return false;
}

bool LargeNum::leq(const LargeNum& number2){
    return (less(number2) || equal(number2));
}
bool LargeNum::geq(const LargeNum& number2){
    return (greater(number2) || equal(number2));
}

LargeNum LargeNum::add(const LargeNum& number2) { 
    if (negative == false && number2.negative) {
        LargeNum temp = number2;
        temp.negative = false;
        return subtract(temp);

    } else if (negative && number2.negative == false) {
        LargeNum temp;
        temp = number2;
        LargeNum temp1;

        temp1.numVec = numVec;
        temp1.negative = negative;
        temp1.dotPos = dotPos;

        temp1.negative = false;
        return temp.subtract(temp1);
    }

    int length1 = numVec.size();
    int length2 = number2.numVec.size();

    int dotPos1 = dotPos;
    int dotPos2 = number2.dotPos;

    int dotPos = max(dotPos1, dotPos2);

    int fracLen1 = length1 - dotPos1;
    int fracLen2 = length2 - dotPos2;
    int fracLen = max(fracLen1, fracLen2);

    vector<char> temp1 = numVec;
    vector<char> temp2 = number2.numVec;

    while (temp1.size() - dotPos1 < fracLen) temp1.push_back('0');
    while (temp2.size() - dotPos2 < fracLen) temp2.push_back('0');

    while (dotPos1 < dotPos2) {
        temp1.insert(temp1.begin(), '0');
        ++dotPos1;
    }
    while (dotPos2 < dotPos1) {
        temp2.insert(temp2.begin(), '0');
        ++dotPos2;
    }

    int length = temp1.size();
    vector<char> numSum(length + 1, '0');

    int carry = 0;
    for (int i = length - 1; i >= 0; --i) {
        int digit1 = temp1[i] - '0';
        int digit2 = temp2[i] - '0';
        int sum = digit1 + digit2 + carry;

        numSum[i + 1] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry){
        numSum[0] = '1';
        ++dotPos;
    }
    else numSum.erase(numSum.begin());

    while (numSum.back() == '0' && numSum.size() > dotPos + 1) {
        numSum.pop_back();
    }

    LargeNum ans;
    ans.negative = negative && number2.negative;
    ans.numVec = numSum;
    ans.dotPos = dotPos;

    return ans;
}

LargeNum LargeNum::subtract(const LargeNum& number2) {        
    if(number2.negative != false){
        LargeNum temp = number2;
        temp.negative = false;
        return add(temp);
    }

    else if(negative != false && number2.negative == false){
        LargeNum temp = number2;
        temp.negative = true;
        return add(temp);
    }

    bool isNegative = false;
    vector<char> temp1, temp2;
    int dotPos1, dotPos2;

    if(less(number2)){
        temp1 = number2.numVec;
        temp2 = numVec;
        dotPos1 = number2.dotPos;
        dotPos2 = dotPos;
        isNegative = true;
    }else{
        temp1 = numVec;
        temp2 = number2.numVec;
        dotPos1 = dotPos;
        dotPos2 = number2.dotPos;
    }
    int dotPos = max(dotPos1, dotPos2);

    int length1 = temp1.size();
    int length2 = temp2.size();

    int fracLen1 = length1 - dotPos1;
    int fracLen2 = length2 - dotPos2;
    int fracLen = max(fracLen1, fracLen2);

    for (int i = 0; i < fracLen - fracLen1; ++i)
        temp1.push_back('0');

    for (int i = 0; i < fracLen - fracLen2; ++i)
        temp2.push_back('0');

    int size = temp1.size();
    int j = size - 1;
    int k = temp2.size() - 1;

    for (int i = size - 1; i >= 0; --i) {
        int digit1 = (j >= 0) ? temp1[j--] - '0' : 0;
        int digit2 = (k >= 0) ? temp2[k--] - '0' : 0;

        if (digit1 < digit2) {
            int pos = i - 1;
            while (pos >= 0 && temp1[pos] == '0') {
                temp1[pos] = '9';
                --pos;
            }
            if (pos >= 0) --temp1[pos];
            digit1 += 10;
        }

        temp1[i] = (digit1 - digit2) + '0';
    }

    while (temp1.size() > 1 && temp1[0] == '0' && dotPos != 1) {
        temp1.erase(temp1.begin());
        dotPos--;
    }

    while (temp1.size() > dotPos + 1 && temp1.back() == '0') {
        temp1.pop_back();
    }

    LargeNum ans;
    ans.negative = false;
    if(isNegative){
        ans.negative = true;
    }

    ans.numVec = temp1;
    ans.dotPos = dotPos;

    return ans;
}

LargeNum LargeNum::multiply(const LargeNum& number2) {
    LargeNum zero = convert("0");
    if (zero.equal(number2)) {
        return zero;
    }

    bool isNegative = (negative && !number2.negative) || (!negative && number2.negative);

    vector<char> temp1 = numVec;
    vector<char> temp2 = number2.numVec;

    int length1 = temp1.size();
    int length2 = temp2.size();
    int length = length1 + length2;

    int dotPos1 = dotPos;
    int dotPos2 = number2.dotPos;

    vector<char> temp(length, '0');

    for (int i = length1 - 1; i >= 0; --i) {
        for (int j = length2 - 1; j >= 0; --j) {
            int mul = (temp1[i] - '0') * (temp2[j] - '0');
            int sum = (temp[i + j + 1] - '0') + mul;

            temp[i + j + 1] = (sum % 10) + '0';
            temp[i + j] = (temp[i + j] - '0') + (sum / 10) + '0';
        }
    }

    int dotPos = dotPos1 + dotPos2;

    if (temp.empty()) {
        temp.push_back('0');
        dotPos = 1;
    }

    while (temp.size() > 1 && temp[0] == '0' && (dotPos != 1)) {
        temp.erase(temp.begin());
        dotPos--;
    }

    while (temp.size() > dotPos + 1 && temp.back() == '0') {
        temp.pop_back();
    }

    int maxSize = dotPos + PRECISION;
    if (temp.size() > maxSize) {
        temp.resize(maxSize);
    }

    LargeNum ans;
    ans.negative = isNegative;
    ans.numVec = temp;
    ans.dotPos = dotPos;

    return ans;
}

void LargeNum::shiftDot(int shift) {
    int newDotPos = dotPos + shift;

    if (newDotPos >= static_cast<int>(numVec.size())) {
        int zerosNeeded = (newDotPos + 1) - numVec.size();
        for(int i = 0; i < zerosNeeded; ++i)
            numVec.push_back('0');
    }
    
    else if (newDotPos < 0) {
        int zerosNeeded = -newDotPos;
        for(int i = 0; i < zerosNeeded; ++i) {
            numVec.insert(numVec.begin(), '0');
        }
        newDotPos = 0;
    }

    while (numVec.size() > 1 && numVec[0] == '0' && newDotPos != 1) {
        numVec.erase(numVec.begin());
        newDotPos--;
    }

    dotPos = newDotPos;
}


LargeNum LargeNum::divide(const LargeNum& number2) {
    LargeNum zero;
    zero = convert("0");


    if (zero.equal(number2)) throw invalid_argument("Wrong input");
    if(equal(number2))
        return convert("1");


    bool isNegative = negative && !number2.negative || !negative && number2.negative;

    LargeNum remainderObj;
    remainderObj  = convert("0");

    vector<char> result;

    LargeNum tempNum2 = number2;
    tempNum2.negative = false;

    LargeNum tempNum1;

    tempNum1.negative = negative;
    tempNum1.numVec = numVec;
    tempNum1.dotPos = dotPos;

    while (tempNum1.numVec.size() > tempNum1.dotPos + 1 && tempNum1.numVec.back() == '0') {
        tempNum1.numVec.pop_back();
    }

    while (tempNum2.numVec.size() > tempNum2.dotPos + 1 && tempNum2.numVec.back() == '0') {
        tempNum2.numVec.pop_back();
    }

    LargeNum temp2;
    temp2 = tempNum2;

    LargeNum temp1;
    temp1 = tempNum1;

    LargeNum ten = convert("10");

    int shift1 = temp1.numVec.size() - temp1.dotPos;
    int shift2 = temp2.numVec.size() - temp2.dotPos;
    int shift = max(shift1, shift2);

    temp1.shiftDot(shift);
    temp2.shiftDot(shift);

    for (char digit : temp1.numVec) {
        remainderObj.shiftDot(1);
        remainderObj = remainderObj.add(convert(string(1, digit)));

        int count = 0;
        while (remainderObj.geq(temp2)) {
            remainderObj = remainderObj.subtract(temp2);
            ++count;
        }

        string temp = to_string(count);
        for(char a : temp)
            result.push_back(a);
    }

    int dotPos = result.size() - 1;

    while (result.size() > 1 && result[0] == '0' && (dotPos != 1)) {
        result.erase(result.begin());
        --dotPos;
    }

    for (int i = 0; i < PRECISION + 1; ++i) {
        remainderObj.shiftDot(1);

        int count = 0;
        while (remainderObj.geq(temp2)) {
            remainderObj = remainderObj.subtract(temp2);
            ++count;
        }

        string temp = to_string(count);
        for (char a : temp) result.push_back(a);
    }

    while (result.size() > dotPos + 1 && result.back() == '0') {
        result.pop_back();
    }

    LargeNum ans;
    ans.numVec = result;
    ans.negative = isNegative;
    ans.dotPos = dotPos;

    return ans;
}

LargeNum LargeNum::operator+(const LargeNum& Number2){
    return add(Number2);
}

LargeNum LargeNum::operator-(const LargeNum& Number2){
    return subtract(Number2);
}

LargeNum LargeNum::operator*(const LargeNum& Number2){
    return multiply(Number2);
}

LargeNum LargeNum::operator/(const LargeNum& Number2){
    return divide(Number2);
}

LargeNum LargeNum::operator%(const LargeNum& Number2){
    return mod(Number2);
}

bool LargeNum::operator>(const LargeNum& Number2){
    return greater(Number2);
}

bool LargeNum::operator<(const LargeNum& Number2) const{
    return less(Number2);
}

bool LargeNum::operator>=(const LargeNum& Number2){
    return geq(Number2);
}

bool LargeNum::operator<=(const LargeNum& Number2){
    return leq(Number2);
}

bool LargeNum::operator==(const LargeNum& Number2){
    return equal(Number2);
}

bool LargeNum::operator!=(const LargeNum& Number2){
    return notEqual(Number2);
}

void LargeNum::operator=(const LargeNum& number2){
    copy(number2);
}

std::ostream& operator<<(std::ostream& os, const LargeNum& number2) {
    os << toStr(number2);
    return os;
}

LargeNum LargeNum::mod(const LargeNum& number2) {
    LargeNum number1;
    number1.negative = negative;
    number1.dotPos = dotPos;
    number1.numVec = numVec;
    
    if (number1 == number2) return convert("0");
    if (number1 < number2 && number1.negative == false && number2.negative == false) return number1;
    if (convert("0") == number2) throw invalid_argument("Wrong input");

    LargeNum dividend = number1 / number2;

    if(dividend == convert("0"))
        return convert("0");

    string rez = "0.";

    for(int i = dividend.dotPos; i < dividend.numVec.size(); ++i){
        rez += dividend.numVec[i];
    }

    LargeNum remainder = convert(rez);

    remainder.negative = number1.negative ^ number2.negative;
    return remainder * number2;
}