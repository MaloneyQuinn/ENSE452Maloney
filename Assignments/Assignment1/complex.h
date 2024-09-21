/**
Name: Quinn Maloney
SID: 200431628
File: complex.h
Description: This contains the information for the 
ComplexNumber class as well as other function
declarations.
*/

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ComplexNumber
{
private:

    double real;
    double imaginary;
    bool divideByZero;

public:

    ComplexNumber();
    void setReal(double);
    void setImaginary(double);
    void setDivideByZero(bool);
    double getReal();
    double getImaginary();
    bool getDivideByZero();
    void printNumber();

};

ComplexNumber addition(ComplexNumber, ComplexNumber);
ComplexNumber subtraction(ComplexNumber, ComplexNumber);
ComplexNumber multiplication(ComplexNumber, ComplexNumber);
ComplexNumber division(ComplexNumber, ComplexNumber);
bool getNumbers(string, string, ComplexNumber&);
void printResult(ComplexNumber);
bool getInput(string, ComplexNumber&, ComplexNumber&);



#endif COMPLEX_H

