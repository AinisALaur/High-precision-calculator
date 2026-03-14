# High precision calculator

## Table of Contents
- [About](#about)
- [Installation & setup](#installation)
- [Usage](#Usage)
- [License](#license)

## About
This is a program that allows to perform arithmetic calculations beyond the capabilities of standard C++ libraries. The current implementation works with 100 digit after decimal point precision.
The program can calculate the square root of a number, the natural logarithm, factorial, raise it to a power, find the next prime, calculate the sin value, average, and get the PI value.

## Installation & setup
Download all files and run the following commands:

g++ -c class.cpp -o class.o

g++ -c extra.cpp -o extra.o

g++ -c test.cpp -o test.o

g++ class.o extra.o test.o -o program.exe

Finally run the *program.exe*

Originally the test.cpp is used for fast and proper testing of the program, where the demo.cpp is used for simple tests.

## Usage
You may view the examples to create and define the LargeNum object in the demo.cpp, if you want to calcualte specific functions you will need to review the test.cpp.
For example if you want to calculate the Log value of 123456789012345678901234567890 you will need to run the ./program.exe and input such sequence:

4

123456789012345678901234567890

Output:
12345678901234567890123456789066.985688719142977389286282557964543815516011249012772786520489851549533755129412108518911647280566878

## License
This project currently has no license assigned. All rights reserved until a license is chosen.
