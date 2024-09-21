/**
Name: Quinn Maloney
SID: 200431628
File: complex.cpp
Description: This contains the definitions for the 
different functions declared in complex.h.
*/

#include "complex.h"

ComplexNumber::ComplexNumber()
{
    real = 0;
    imaginary = 0;
    divideByZero = false;
}

void ComplexNumber::setReal(double input)
{
    real = input;
}

void ComplexNumber::setImaginary(double input)
{
    imaginary = input;
}

void ComplexNumber::setDivideByZero(bool input)
{
    divideByZero = input;
}

double ComplexNumber::getReal()
{
    return real;
}

double ComplexNumber::getImaginary()
{
    return imaginary;
}

bool ComplexNumber::getDivideByZero()
{
    return divideByZero;
}

void ComplexNumber::printNumber()
{
    if (imaginary < 0)
        cout << real << " - j " << imaginary << endl;
    else
        cout << real << " + j " << imaginary << endl;
}

ComplexNumber addition(ComplexNumber firstNumber, 
    ComplexNumber secondNumber)
{
    ComplexNumber result;
    result.setReal(firstNumber.getReal() + secondNumber.getReal());
    result.setImaginary(firstNumber.getImaginary() 
        + secondNumber.getImaginary());
    return result;
}

ComplexNumber subtraction(ComplexNumber firstNumber, 
    ComplexNumber secondNumber)
{
    ComplexNumber result;
    result.setReal(firstNumber.getReal() - secondNumber.getReal());
    result.setImaginary(firstNumber.getImaginary() 
        - secondNumber.getImaginary());
    return result;
}

ComplexNumber multiplication(ComplexNumber firstNumber, 
    ComplexNumber secondNumber)
{
    ComplexNumber result;
    result.setReal((firstNumber.getReal() * secondNumber.getReal()) 
        - (firstNumber.getImaginary() * secondNumber.getImaginary()));
    result.setImaginary((firstNumber.getReal() * secondNumber.getImaginary())
        + (firstNumber.getImaginary() * secondNumber.getReal()));
    return result;
}

ComplexNumber division(ComplexNumber firstNumber,
    ComplexNumber secondNumber)
{
    ComplexNumber result;
    if (secondNumber.getReal() == 0 && secondNumber.getImaginary() == 0)
    {
        cerr << "error code : 4 : divide by zero" << endl;
        result.setDivideByZero(true);
        return result;
    }

    result.setReal(((firstNumber.getReal() * secondNumber.getReal())
        + (firstNumber.getImaginary() * secondNumber.getImaginary())) 
        / ((secondNumber.getReal() * secondNumber.getReal())
        + (secondNumber.getImaginary() * secondNumber.getImaginary())));
    result.setImaginary(((firstNumber.getImaginary() * secondNumber.getReal())
        - (firstNumber.getReal() * secondNumber.getImaginary()))
        / ((secondNumber.getReal() * secondNumber.getReal())
        + (secondNumber.getImaginary() * secondNumber.getImaginary())));
    return result;
}

bool getNumbers(string realInput, string imaginaryInput, ComplexNumber& result)
{
    string value;
    bool decimal = false;
    bool e = false;
    bool minus = false;
    for (int i = 0; i < realInput.length(); i++)
    {
        if (isdigit(realInput[i]))
            value += realInput[i];

        else if (realInput[i] == '.' && decimal == false)
        {
            value += realInput[i];
            decimal = true;
        }

        else if (realInput[i] == '-' && minus == false)
        {
            value += realInput[i];
            minus = true;
        }

        else if (realInput[i] == 'e' && e == false)
        {
            e == true;
            value += realInput[i];
        }

        else
        {
            cerr << "error code : 3 : extra arguments" << endl;
            return false;
        }
    }
    result.setReal(stod(value));

    decimal = false;
    e = false;
    value = "";
    minus = false;

    for (int i = 0; i < imaginaryInput.length(); i++)
    {
        if (isdigit(imaginaryInput[i]))
            value += imaginaryInput[i];

        else if (imaginaryInput[i] == '.' && decimal == false)
        {
            value += imaginaryInput[i];
            decimal = true;
        }

        else if (realInput[i] == '-' && minus == false)
        {
            value += realInput[i];
            minus = true;
        }

        else if (imaginaryInput[i] == 'e' && e == false)
        {
            e == true;
            value += imaginaryInput[i];
        }

        else
        {
            cerr << "error code : 3 : extra arguments" << endl;
            return false;
        }
    }
    result.setImaginary(stod(value));

    return true;
}

bool getInput(string input, ComplexNumber& firstNumber, ComplexNumber& secondNumber)
{
    vector<string> values;
    string stringValue;
    bool error;
    int i = 0;
    
    while (input[i] == ' ')
        i++;

    for (int y = 0; y < 4; y++)
    {
        stringValue = "";
        while(input[i] != ' ' && i < input.length())
        {
            if (input[i] != ' ' && input[i] != '/n')
                stringValue += input[i];
            i++;
        }
        while (input[i] == ' ')
            i++;
        if (stringValue.empty() == true)
        {
            cerr << "error code : 2 : missing arguments" << endl;
            return false;
        }

        values.push_back(stringValue);
    }

    while (i != input.length())
    {
        if (input[i] != ' ')
        {
            cerr << "error code : 3 : extra arguments" << endl;
            return false;
        }
        i++;
    }

    error = getNumbers(values[0], values[1], firstNumber);
    if (error == false)
        return false;
    error = getNumbers(values[2], values[3], secondNumber);
    if (error == false)
        return false;
    return true;
    
}





