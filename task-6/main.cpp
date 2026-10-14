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

int takeNumInput() {
    // Have inputNum default to a number outside of range - Makes do while loop run until a correct input
    // is given. If this was 0, if a string was inputted, the cin would fail, but the inputNum would be used
    // in the rest of the programm with a value of 0 or cause loop errors
    int inputNum = -1;
    do {
        cout << " - Please enter a number between 0-100: ";
        cin >> inputNum;
        if (cin.fail()) {
            cerr << "ERROR: That is not an integer." << endl;
        }
        else if (inputNum < 0 || inputNum > 100) {
            cerr << "ERROR: That number is out of bounds." << endl;
        }
    } while (inputNum < 0 || inputNum > 100);
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
    int randNum = random(0, 100);
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