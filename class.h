#ifndef CLASS_H
#define CLASS_H

#include<iostream>
#include <vector>

class LargeNum {
private:
    std::vector<char> numVec;
    bool negative;
    int dotPos;
public:
    void shiftDot(int shift);
    void setVec(std::vector<char> vector);
    void setNegative(bool negativity);
    void setDotPos(int dotPosition);
    std::vector<char> getVec()const;
    bool isNegative()const;
    int getDotPos()const;
    int getSize();

    LargeNum add(const LargeNum& number);
    LargeNum subtract(const LargeNum& number); 
    LargeNum multiply(const LargeNum& number); 
    LargeNum divide(const LargeNum& number);
    LargeNum mod(const LargeNum& number);
    bool equal(const LargeNum& number);
    bool notEqual(const LargeNum& number);
    bool greater(const LargeNum& number);
    bool less(const LargeNum& number)const;
    bool leq(const LargeNum& number);
    bool geq(const LargeNum& number);
    void copy(const LargeNum& number);

    void operator=(const LargeNum &number);
    LargeNum operator+(const LargeNum &number);
    LargeNum operator-(const LargeNum &number);
    LargeNum operator*(const LargeNum &number);
    LargeNum operator/(const LargeNum &number);
    LargeNum operator%(const LargeNum &number);
    bool operator==(const LargeNum& Number2);
    bool operator<=(const LargeNum& Number2);
    bool operator>=(const LargeNum& Number2);
    bool operator<(const LargeNum& Number2)const;
    bool operator>(const LargeNum& Number2);
    bool operator!=(const LargeNum& Number2);
    friend std::ostream& operator<<(std::ostream& os, const LargeNum& number2);

    LargeNum roundToPrecision(int precision) const;
};

LargeNum convert(std::string num);

#endif