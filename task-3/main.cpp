/*
    Assessment 1 - Challenge 3
    Task: Calculator
    Uses std::cin to prompt the user for a single number from the command line, uses input checking to
        ensure it is the correct datatype, and then if correct, perfrom multiple calculations on the
        inputted number
*/

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    // Inputted number - Must be float in order to allow for decimal numbers, and must be signed for
    // negatives to be valid
    float x;
    cout << "Please enter your chosen number (x): ";
    cin >> x;

    // Check whether the inputted data was of an invalid type
    // If a wrong type value is inputted, the cin will fail, and the errors will be called
    // Discovered through StackOverflow "How do I check if input is an integer/string?"
    if (cin.fail()) {
        cerr << "ERROR: You entered a string, this is not a valid number." << endl;
        int ERROR_STRING_INPUT = -1;
        return ERROR_STRING_INPUT;
    }

    // Calculate following metrics
    cout << "Negation of x: " << -x << endl;
    cout << "Absolute Value of x: " << abs(x) << endl;
    cout << "Square of x: " << pow(x,2) << endl;
    cout << "Cube of x: " << pow(x,3) << endl;
    cout << "Square Root of x: " << sqrtf(x) << endl;
    cout << "Floor Value of x: " << floorf(x) << endl;
    cout << "Ceiling Value of x: " << ceilf(x) << endl;
    cout << "Rounded Value of x: " << roundf(x) << endl;
}