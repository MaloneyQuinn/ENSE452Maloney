/**
Name: Quinn Maloney
SID: 200431628
File: main.cpp
Description: The main function call for assignment 1's 
complex calculator.
*/

#include "complex.h"

int main()
{
    string input;
    string realInput = "";
    string imaginaryInput = "";
    double realValue;
    bool flag = true;
    ComplexNumber firstNumber;
    ComplexNumber secondNumber;
    ComplexNumber result;

    while (1)
    {
        cerr << "Enter exp: ";
        cin >> input;

        if (input == "a" || input == "A")
        {
            getline(cin, input);
            flag = getInput(input, firstNumber, secondNumber);
            if (flag == true)
            {
                result = addition(firstNumber, secondNumber);
                result.printNumber();
            }     
        }

        else if (input == "s" || input == "S")
        {
            getline(cin, input);
            flag = getInput(input, firstNumber, secondNumber);
            if (flag == true)
            {
                result = subtraction(firstNumber, secondNumber);
                result.printNumber();
            }
        }

        else if (input == "m" || input == "M")
        {
            getline(cin, input);
            flag = getInput(input, firstNumber, secondNumber);
            if (flag == true)
            {
                result = multiplication(firstNumber, secondNumber);
                result.printNumber();
            }
        }

        else if (input == "d" || input == "D")
        {
            getline(cin, input);
            flag = getInput(input, firstNumber, secondNumber);
            if (flag == true)
            {
                result = division(firstNumber, secondNumber);
                if (!result.getDivideByZero())
                    result.printNumber();
            }
        }

        else if (input == "q" || input == "Q")
        {
            return 0;
        }

        else
            cerr << "error code: 1: illegal command" << endl;
    }
}
