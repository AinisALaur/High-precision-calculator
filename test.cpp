#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>

// other includes and definitions
#include<vector>
#include<limits>

#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <math.h>
#include <map>

#define ROUNDPRECISION 99

#include "class.h"
#include "extra.h"

/* YOUR CODE HERE */

using namespace std;

// define your datatype here
typedef LargeNum myType;

myType epsilon = convert("0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

// compute a factorial
myType myFactorial(int n); 	

// finds the next prime, bigger than n					
myType myPrime(myType n); 	

// finds d to the power of (positive) p					
myType myPow(double d, int p); 	

// finds (natural) logarithm of d				
myType myLog(double d); 

// finds sinus of d						
myType mySin(double d); 

// finds square root of d						
myType mySqrt(double d); 

// finds a value of PI with n digits of precision (zeroes afterwards)						
myType myPi(int n); 		

// computes an average of n valus in an array 					
myType myAvg(myType *data, int n); 		

// search for a value in an array of n numbers and return an index		
int myFind(myType *data, int n, myType value); 	

// sorts data in an array of n numbers by (optimized) bubble sort algorithm
void mySort(myType *data, int n); 				

myType myFactorial(int n){
    if(n < 0 )
        throw invalid_argument("Wrong input");
    
    myType number = convert(to_string(n));
    myType result = convert("1");
    myType one = convert("1");

    while(number > one){
        result = result * number;
        number = number - one;
    }

    return result;
}

myType myPrime(myType n){
    myType temp;
    temp = n;

    if (temp % convert("2") == convert("0")) {
        temp = temp + convert("1");
    } else {
        temp = temp + convert("2");
    }

    while(!isPrime(temp)){
        temp = temp + convert("1");
    }

    return temp;
}

myType myPow(double d, int p){
    myType multiplier = convert(doubleToString(d));
    myType rez;
    rez = multiplier;
    
    if(p > 0){
        for(int i = 1; i < p; ++i){
            rez = rez * multiplier;
        }
    }else if(p < 0){
        for(int i = 1; i < p; ++i){
            rez = rez / multiplier;
        }
    }else{
        return convert("1");
    }

    return rez;
}

myType lnApprox(LargeNum d){
    myType one = convert("1");
    myType approx = convert("0");
    myType e = convert("2.71");
    
    while(d > one){
        d = d / e;
        approx = approx + one;
    }
    return approx;
}

myType myLog(double d){
    if(d <= 0 ){
        throw invalid_argument("Wrong input");
    }

    if (d < 1) {
        return convert("-1") * myLog(1.0 / d);
    }

    myType num = convert(doubleToString(d));

    myType one = convert("1");
    myType two = convert("2");
    myType zero = convert("0");

    map<myType, int> factorized;

    while(num % two == zero){
        if(factorized.count(two) == 0)
            factorized[two] = 0;

        num = num / two;
        ++factorized[two];
    }

    for (myType i = convert("3"); i*i <= num; i = i + two) {
        while (num % i == zero) {
            if(factorized.count(i) == 0)
                factorized[i] = 0;

            num = num / i; 
            ++factorized[i];
        } 
    }

    if (num > one){
        factorized[num] = 1;
    }

    myType rez = zero;
    map<myType, myType> logs;

    for(auto it : factorized){
        myType factor = it.first;
        int count = it.second;

        myType logValue;

        if (factor == one) {
            logValue = zero;
        } else {
            myType x = lnApprox(factor);
            myType prev;

            while(true) {
                prev = x;
                myType exp_x = myExp(x);

                x = x - one + (factor / exp_x);

                myType difference = (prev > x) ? (prev - x) : (x - prev);
                if (difference < epsilon) {
                    break;
                }
            }
            logValue = x;
        }

        rez = rez + (convert(to_string(count)) * logValue);
    }

    return rez;
}

myType mySin(double d){   
    const myType twoPi = convert("6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413596429617302656461329418768921910116446345071881626"); 

    myType x = convert(doubleToString(d)) % twoPi;

    myType current_num;
    current_num = x;

    myType rez;
    rez = x;

    int sym = -1;

    myType factorial;
    factorial = convert("1");

    myType prev;

    int i = 3;
    while(true){
        prev = rez;
        current_num = current_num * x * x;
        factorial = factorial * convert(to_string(i)) * convert(to_string(i - 1));
        rez = rez + (convert(to_string(sym)) * (current_num / factorial));
        sym *= -1;
        i+=2;
        myType difference = prev - rez > rez - prev ? prev - rez : rez - prev;
        if (difference < epsilon)
            break;
    }

    return rez;
}

myType mySqrt(double d) {
    if(d < 0)
        throw invalid_argument("Wrong input");

    myType x;

    x = convert(doubleToString(d));

    myType x1;
    if (d < 1) {
        x1 = convert(doubleToString(d * 2));
    } else {
        x1 = convert(doubleToString(d / 2));
    }

    myType prev;
    prev = convert("0");

    myType two = convert("2");
    while (true){
        prev = x1;
        x1 = (x1 + (x / x1)) / two;
        myType difference = prev - x1 > x1 - prev ? prev - x1 : x1 - prev;
        if (difference < epsilon)
            break;
    }

    return x1;
}

myType myPi(int n){
    if(n < 0 )
        throw invalid_argument("Wrong input");
    
    myType term1 = myArctan(convert("0.2"));
    myType term2 = myArctan(convert("1") / convert("239"));
    myType rez = convert("16") * term1 - convert("4") * term2;
    return rez.roundToPrecision(n);
}

myType myAvg(myType *data, int n){
    if(n <= 0 )
        throw invalid_argument("Wrong input");

    myType sum = convert("0");

    for(int i = 0; i < n; ++i){
        sum = sum + data[i];
    }

    return sum / convert(to_string(n));
}

int myFind(myType *data, int n, myType value){
    if(n <= 0 )
        throw invalid_argument("Wrong input");
    
    for(int i = 0; i < n; ++i){
        if(data[i] == value)
            return i;
    }
    return -1;
}

void mySort(myType *data, int n){
    if(n <= 0 )
        throw invalid_argument("Wrong input");
    for(int i = 0; i < n - 1; ++i){
        int changed = 0;
        for(int j = 0; j < n - 1 - i; ++j){
            if(data[j] > data[j+1]){
                changed = 1;
                myType temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
        if(changed == 0)
            break;
    }
}

/* DO NOT MODIFY CODE BELOW */
int main(){
	while(1){
		int x = -1;
		cin >> x;	
		if (x == 0)
			break;
		string s;
		double d;
		int n;
		myType *data = NULL;
		string output;

		switch(x){
			case 1:
				cin >> n;
				cout << (output = toStr(myFactorial(n))) << endl;
				break;
			case 2:
				cin >> s;
				cout << (output = toStr(myPrime(convert(s)))) << endl;
				break;
			case 3:
				int p;
				cin >> d >> p;
				cout << (output = toStr(myPow(d, p))) << endl;
				break;
			case 4:
                cin>>d;
				cout << (output = toStr(myLog(d))) << endl;
				break;
			case 5:
				cin >> d;
				cout << (output = toStr(mySin(d))) << endl;
				break;
			case 6:
				cin >> d;
				cout << (output = toStr(mySqrt(d))) << endl;
				break;
			case 7:
				cin >> n;
				cout << (output = toStr(myPi(n))) << endl;
				break;
			case 8:
				cin >> n;	
				data = new myType[n];		
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				cout << (output = toStr(myAvg(data, n))) << endl;
				delete [] data;
				break;
			case 9:
				cin >> n;			
				data = new myType[n];
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				cin >> s;
				int f;			
				cout << (f = myFind(data, n, convert(s))) << endl;
				delete [] data;
				break;
			case 10:
				cin >> n;			
				data = new myType[n];
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				mySort(data, n);
				for(int i = 0; i < n; ++i){
					cout << (output = toStr(data[i])) << endl;
				}
				delete [] data;
				break;
		}
	}
	return 0;	
}