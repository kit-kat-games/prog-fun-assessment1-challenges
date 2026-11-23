/*
    Assessment 1 - Challenge 3
    Task: Calculator
    Uses std::cin to prompt the user for a single number from the command line, uses input checking to
        ensure it is the correct datatype, and then if correct, perfrom multiple calculations on the
        inputted number
*/

#include <iostream>
#include <string>
using namespace std;

const int ERROR_STRING_INPUT = 1;
const int ERROR_INVALID_NUMBER = 2;

int main(int argc, char* argv[])
{
    // Inputted number - Must be float/double in order to allow for decimal numbers, and must be signed for
    // negatives to be valid. Must be long double to allow a greater size of number to be inputted and calculated
    long double x = 0.0f;
    string input;
    cout << "Please enter your chosen number (x): ";
    getline(cin, input);

    bool validInput = true;
    bool seenNum = false; bool onNum = false;
    bool seenMinusSign = false; bool seenDecimalPoint = false;
    bool seenNumWholePart = false; bool onNumWholePart = false;
    bool seenNumFractPart = false; bool onNumFractPart = false;
    bool fillWholePartWithZero = false; bool fillFractPartWithZero = false;
    // Checks that there is a single integer value within the string, with availability for spaces before
    // and after the number
    for (char c : input) {
        // If already proven invalid, do not need to check any further characters
        if (!validInput) { continue; }
        // If any invalid characters within
        else if (!isdigit(c) && !isspace(c) && c != '-' && c != '.') { 
            validInput = false; 
            cerr << "ERROR: Invalid input. That is a string, not a number." << endl;
            return ERROR_STRING_INPUT;
        }
        // If any digits present after the number finishes
        else if (isdigit(c) && seenNum && !onNum) { validInput = false; }
        // If multiple decimal points present
        else if (c == '.' && seenDecimalPoint) { validInput = false; }
        // If a decimal point present after number finishes
        else if (c == '.' && seenNum && !onNum) { validInput = false; }
        // If multiple minus signs present
        else if (c == '-' && seenMinusSign) { validInput = false; }
        // If a minus sign present anywhere after the start of the num
        else if (c == '-' && seenNum) { validInput = false; }
        // If there is a space between a minus sign and the number
        else if (isspace(c) && seenMinusSign && !seenNum) { validInput = false; }

        // Seeing a valid minus sign
        else if (c == '-' && !seenMinusSign && !seenNum) { seenMinusSign = true; }
        // Entering the start of the number
        else if (isdigit(c) && !seenNumWholePart) { seenNum = true; onNum = true; seenNumWholePart = true; onNumWholePart = true; }
        // If go straight to decimal point with no digits before hand - We will fill this empty space with a zero. Example: .7 -> 0.7 or -.31 -> -0.31
        else if (c == '.' && !seenNumWholePart) { seenNumWholePart = true; seenNum = true; onNum = true; seenDecimalPoint = true; fillWholePartWithZero = true; }
        // Seeing a valid decimal point after a non-empty whole number part
        else if (c == '.' && seenNumWholePart) { onNumWholePart = false; seenDecimalPoint = true; }
        // Entering the fractional part of the number
        else if (isdigit(c) && seenNumWholePart && seenDecimalPoint && !onNumWholePart && !seenNumFractPart) { seenNumFractPart = true; onNumFractPart = true; }
        // Leaving the end of the number
        else if (isspace(c) && onNum) { onNum = false; onNumWholePart = false; onNumFractPart = false; }
    }

    if (seenDecimalPoint && !seenNumFractPart) { fillFractPartWithZero = true; }


    if (!validInput || !seenNum) {
        cout << "ERROR: Invalid Input. That is not a valid number." << endl;
        return ERROR_INVALID_NUMBER;
    }
    else {
        string numString;
        if (fillWholePartWithZero) { numString += '0'; }
        for (char c : input) {
            if (isdigit(c) || c == '.') { numString += c; }
        }
        if (fillFractPartWithZero) { numString += '0'; }
        x = stof(numString);
        if (seenMinusSign) { x *= -1; }
    }

    // Calculate and display the following metrics
    cout << "Negation of x: " << -x << endl;
    cout << "Absolute Value of x: " << abs(x) << endl;
    cout << "Square of x: " << pow(x,2) << endl;
    cout << "Cube of x: " << pow(x,3) << endl;
    cout << "Square Root of x: " << sqrtf(x) << endl;
    cout << "Floor Value of x: " << floorf(x) << endl;
    cout << "Ceiling Value of x: " << ceilf(x) << endl;
    cout << "Rounded Value of x: " << roundf(x) << endl;
}