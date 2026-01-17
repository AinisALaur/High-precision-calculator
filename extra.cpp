#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>

#include <cmath>

using namespace std;

#include "extra.h"

#define ROUNDPRECISION 99

const LargeNum epsilon = convert("0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");


string toStr(const LargeNum& number) {
    LargeNum temp = number.roundToPrecision(ROUNDPRECISION);
    
    string rez;

    if (number.isNegative()) 
        rez += '-';

    vector<char> numVec = temp.getVec();
    int dotPos = temp.getDotPos();

    for (int i = 0; i < temp.getVec().size(); ++i) {
        if (i == dotPos) 
            rez += '.';
        rez += temp.getVec()[i];
    }

    return rez;
}

LargeNum convert(string num) {
    if(!validInput(num)){
        throw invalid_argument("Wrong input");
    }

    int start = 0;    
    LargeNum number;

    if (num[0] == '-') {
        number.setNegative(true);
        ++start;
    } else {
        number.setNegative(false);
    }


    vector<char> numerical;
    int dotPos = -1;
    for (int i = start; i < num.length(); ++i) {
        if (num[i] == '.') {
            dotPos = numerical.size();
        } else {
            numerical.push_back(num[i]);
        }
    }

    if (dotPos == -1) {
        dotPos = numerical.size();
        numerical.push_back('0');
    }

    for(int i = numerical.size() - 1; i > dotPos; --i){
        if(numerical[i] == '0'){
            numerical.pop_back();
        }
        else
            break;
    }

    number.setDotPos(dotPos);
    number.setVec(numerical);

    return number;
}

bool validInput(string number1) {
    if (number1.empty()) {
        return false;
    }
    if (number1[0] == '.') {
        return false;
    }

    bool hasDecimal = false;

    for (int i = 0; i < number1.size(); ++i) {
        if (number1[i] == '-') {
            if (i != 0){
                return false;
            }
        } else if (number1[i] == '.') {
            if (hasDecimal) {
                return false;
            }
            hasDecimal = true;
        } else if (!isdigit(number1[i])) {
            return false;
        }
    }

    return true;
}

LargeNum myArctan(LargeNum x) {
    if (x == convert("0")) 
        return convert("0");
    
    LargeNum sum = x;
    LargeNum term = x;
    LargeNum x_squared = x * x;
    
    int i = 1;
    while (true) {
        term = term * x_squared;
        LargeNum denom = convert(to_string(2*i + 1));
        LargeNum next_term = term / denom;
        
        if (next_term < epsilon) 
            break;
        
        if (i % 2 == 1) {
            sum = sum - next_term;
        } else {
            sum = sum + next_term;
        }
        
        ++i;
    }

    return sum;
}

LargeNum myExp(LargeNum x){
    if (x == convert("0")) 
        return convert("1");
    
    LargeNum one = convert("1");
    LargeNum rez = one;
    LargeNum term = one; 
    LargeNum prev;
    int i = 1;
    
    while(true){
        prev = rez;
        
        term = term * x / convert(to_string(i));
        rez = rez + term;
        
        LargeNum difference = (prev > rez) ? (prev - rez) : (rez - prev);
        if (difference < epsilon)
            break;
            
        ++i;
    }
    
    return rez;
}

bool isPrime(LargeNum number) {
    if (number <= convert("1")){
        return false;
    }

    if (number == convert("2") || number == convert("3")) {
        return true;
    }

    if (number % convert("2") == convert("0") || number % convert("3") == convert("0")){
        return false;
    }

    for (LargeNum i = convert("5"); i * i <= number; i = i + convert("6")) {
        if (number % i == convert("0") || number % (i + convert("2")) == convert("0")) {
            return false;
        }
    }

    return true;
}

string doubleToString(double value) {
    if(value == 0)
        return "0";
    
    int digits_before_decimal = (fabs(value) >= 1) ? static_cast<int>(log10(fabs(value))) + 1 : 1;
    int digits_after_decimal = 14 - digits_before_decimal;

    if (digits_after_decimal < 0) {
        digits_after_decimal = 0;
    }

    ostringstream oss;
    oss << fixed << setprecision(digits_after_decimal) << value;
    string str = oss.str();

    return str;
}