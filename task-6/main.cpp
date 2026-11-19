/*
    Assessment 1 - Challenge 6
    Task: Number Guessing Game
    Uses a custom random function within a header file, prompts the user for a number, and uses the difference
        in order to push the user towards the right number in later guesses
*/

#include "main.h"
#include <iostream>
#include <string>
using namespace std;

const int LOWER_BOUND = 0;
const int UPPER_BOUND = 100;

int takeNumInput() {
    // Have inputNum default to a number outside of range - Makes do while loop run until a correct input
    // is given. If this was 0, if a string was inputted, the cin would fail, but the inputNum would be used
    // in the rest of the programm with a value of 0 or cause loop errors
    int inputNum = -1;
    string input;
    do {
        bool validInput = true;
        cout << " - Please enter a number between 0-100: ";
        getline(cin, input);

        bool seenMinusSign = false; bool seenNum = false; bool onNum = false;
        // Checks that there is a single integer value within the string, with availability for spaces before
        // and after the number
        for (char c : input) {
            // If already proven invalid, do not need to check any further characters
            if (!validInput) { continue; }
            // If any invalid characters within
            else if (!isdigit(c) && !isspace(c) && c != '-') { validInput = false; }
            // If any digits present after the number finishes
            else if (isdigit(c) && seenNum && !onNum) { validInput = false; }
            // If multiple minus signs present
            else if (c == '-' && seenMinusSign) { validInput = false; }
            // If a minus sign present anywhere after the start of the num
            else if (c == '-' && seenNum) { validInput = false; }
            // If there is a space between a minus sign and the number
            else if (isspace(c) && seenMinusSign && !seenNum) { validInput = false; }

            // Seeing a valid minus sign
            else if (c == '-' && !seenMinusSign && !seenNum) { seenMinusSign = true; }
            // Entering the start of the number
            else if (isdigit(c) && !seenNum) { seenNum = true; onNum = true; }
            // Leaving the end of the number
            else if (isspace(c) && onNum) { onNum = false; }
        }

        if (!validInput || !seenNum) {
            cout << "ERROR: That is not an integer." << endl;
            input = "";
        }
        else {
            string numString;
            for (char c : input) {
                if (isdigit(c)) { numString += c; }
            }
            inputNum = stoi(numString);
            if (seenMinusSign) { inputNum *= -1; }
            if (inputNum < LOWER_BOUND || inputNum > UPPER_BOUND) {
                cerr << "ERROR: That number is out of bounds." << endl;
                input = "";
            }
        }
    } while (input == "");
    return inputNum;
}

void outputDifferenceHint(int inputNum, int targetNum) {
    // Output appropiate feedback message based on calculated difference
    int d = abs(inputNum - targetNum);
    if (d >= 50) {
        cout << "Freezing" << endl;
    } 
    // Same as 35 <= d < 50 - Same for the rest of the else if statements
    else if (d >= 35) { 
        cout << "Colder" << endl;
    }
    else if (d >= 25) {
        cout << "Cold" << endl;
    }
    else if (d >= 15) {
        cout << "Warm" << endl;
    }
    else if (d >= 10) {
        cout << "Warmer" << endl;
    }
    else if (d >= 5) {
        cout << "Hot" << endl;
    }
    else if (d >= 3) {
        cout << "Hotter" << endl;
    }
    else if (d >= 1) {
        cout << "Boiling" << endl;
    }
}

int main(int argc, char* argv[])
{
    // Decide random number, output for debug
    int randNum = random(LOWER_BOUND, UPPER_BOUND);
    cout << "For Debugging, the random number is: " << randNum << endl;

    // Game loop - Put logic in outside functions for more readability and better layout
    int guessCount = 0;
    bool gameWon = false;
    while (!gameWon) {
        int inputNum = takeNumInput();
        guessCount++;
        if (inputNum == randNum) {
            cout << "Correct! The answer was " << randNum << endl;
            cout << "Total number of guesses: " << guessCount << endl;
            gameWon = true;
        }
        // If gameWon was true, no difference hint will be printed
        outputDifferenceHint(inputNum, randNum);
    }
}