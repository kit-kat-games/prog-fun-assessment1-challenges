/*
    Assessment 1 - Challenge 9
    Task: Vector2 Class

*/

#include <stdexcept>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Vector2.h"
using namespace std;

enum ERROR {
    ERROR_UNKNOWN,
    ERROR_INVALID_VECTOR,
};

bool isAllowedChar(char c) {
    vector<char> allowedChars = { '[', ',', ']', '.', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' '};
    for (char ac : allowedChars) {
        if (ac == c) {
            return true;
        }
    }
    return false;
}

Vector2 parseInput(string input) {
    vector<char> reqSymbolComponents = { '[', ',', ']' };
    char reqSymbol = reqSymbolComponents[0];

    bool validInput = true;

    bool seenOpenB = false;
    bool seenComma = false;
    bool seenCloseB = false;
    bool seenX = false;
    bool seenY = false;
    bool xHasDecimal = false;
    bool yHasDecimal = false;

    string xPart = "";
    string yPart = "";

    for (int i = 0; i < input.length(); i++) {
        if (!validInput) { break; }

        char c = input[i];

        // Seeing Invalid Character
        if (!isAllowedChar(c)) {
            validInput = false;
        }

        // Seeing Characters Twice
        if (c == '[' && seenOpenB) {
            validInput = false;
        }
        if (c == ',' && seenComma) {
            validInput = false;
        }
        if (c == ']' && seenCloseB) {
            validInput = false;
        }

        // Seeing Characters Before They Should Appear
        if (c == '[' && reqSymbol != '[') {
            validInput = false;
        }
        if (c == ',' && reqSymbol != ',') {
            validInput = false;
        }
        if (c == ']' && reqSymbol != ']') {
            validInput = false;
        }

        // Seeing Seperators Before Seeing The Number That Goes Before : Need To See X Before ',' And Need To See Y Before ']'
        if (c == ',' && !seenX) {
            validInput = false;
        }
        if (c == ']' && !seenY) {
            validInput = false;
        }

        // Anything Before - Allow Spaces
        if (reqSymbol == '[' && c != '[' && !isspace(c)) {
            validInput = false;
        }
        // Anything After - Allow Spaces
        if (reqSymbolComponents.empty() && !isspace(c)) {
            validInput = false;
        }

        if (isdigit(c)) {
            if (!seenX && seenOpenB) {
                seenX = true;
                xPart += c;
            }
            else if (seenX && !seenComma) {
                xPart += c;
            }
            if (!seenY && seenComma) {
                seenY = true;
                yPart += c;
            }
            else if (seenY) {
                yPart += c;
            }
        }
        if (c == '.') {
            if (!seenX && seenOpenB) {
                seenX = true;
                xHasDecimal = true;
                xPart += '.';
            }
            else if (seenX && !xHasDecimal) {
                xHasDecimal = true;
                xPart += '.';
            }
            else if (xHasDecimal && !seenComma) {
                validInput = false;
            }

            if (!seenY && seenComma) {
                seenY = true;
                yHasDecimal = true;
                yPart += '.';
            }
            else if (seenY && !yHasDecimal) {
                yHasDecimal = true;
                yPart += '.';
            }
            else if (yHasDecimal) {
                validInput = false;
            }
        }
        if (c == reqSymbol) {
            reqSymbolComponents.erase(reqSymbolComponents.begin());
            if (reqSymbolComponents.size() > 0) {
                reqSymbol = reqSymbolComponents[0];
            }
            else {
                // Acts as a filler char - Should never be in a vector, so will not matter in any of the checks above
                reqSymbol = '@';    
            }
            if (c == '[') { seenOpenB = true; }
            if (c == ',') { seenComma = true; }
            if (c == ']') { seenCloseB = true; }
        }
    }
    
    if (!validInput) {
        throw ERROR_INVALID_VECTOR;
    }

    float x = stof(xPart);
    float y = stof(yPart);

    return Vector2(x, y);
}

Vector2 createVector(string createRequest = "") {
    while (true) {
        string input = "";
        if (createRequest != "") {
            cout << createRequest;
        }
        getline(cin, input);
        if (cin.fail()) {
            cerr << "[!] ERROR: That is not a string." << endl;
        }
        else if (input == "") {
            cerr << "[!] ERROR: That is an empty string." << endl;
        }
        else {
            try {
                Vector2 vec = parseInput(input);
                return vec;
            }
            catch (const ERROR e) {
                if (e == ERROR_INVALID_VECTOR) { cerr << "[!] ERROR: Invalid format, please use [x, y], like [3.7, 6.1]." << endl; }
            }
        }
    }
    throw ERROR_UNKNOWN;
}

void mode1() {
    Vector2 vec1 = createVector("- Enter vector #1: ");
    Vector2 vec2 = createVector("- Enter vector #2: ");
    cout << endl;

    cout << "Distance between [" << vec1.readX() << ", " << vec1.readY() << "] and [" << vec2.readX() << ", " << vec2.readY() << "] is " << Vector2::Distance(vec1, vec2) << "." << endl;
}

void mode2() {
    const int UPPER_BOUND = 45;
    const int LOWER_BOUND = -45;

    Vector2 player1Pos = createVector("- Enter player #1 pos: ");
    Vector2 viewDirectionVector = createVector("- Enter player #1's view direction: ");
    Vector2 player2Pos = createVector("- Enter player #2 pos: ");
    cout << endl;
    
    // Use cos(theta) = (A dot B) / (Mag(A) * Mag(B))
    Vector2 positionDirectionVector = player2Pos - player1Pos;
    float cosTheta = (Vector2::Dot(positionDirectionVector, viewDirectionVector)) / (positionDirectionVector.Magnitude() * viewDirectionVector.Magnitude());
    float thetaRadians = acos(cosTheta);
    float thetaDegrees = (thetaRadians * 180.0f) / M_PI;
    
    if (thetaDegrees >= LOWER_BOUND && thetaDegrees <= UPPER_BOUND) {
        cout << ">> Player 2 is within Player 1's FoV." << endl;
    }
    else {
        cout << ">> Player 2 is NOT within Player 1's FoV." << endl;
    }
}

int main(int argc, char* argv[])
{
    while (true) {
        cout << ">> What mode would you like to use?" << endl;
        cout << ">> - 1. Distance between two points." << endl;
        cout << ">> - 2. Check if one point is within view cone of another." << endl;
        cout << "- Enter your choice: ";

        string choice;
        getline(cin, choice);
        if (cin.fail()) { 
            cerr << "[!] ERROR: That is not a string." << endl; 
        }
        else if (choice == "") { 
            cerr << "[!] ERROR: That is an empty string." << endl; 
        }

        string whitespaceStrippedChoice;
        for (char c : choice) {
            if (c != '1' && c != '2' && c != ' ') {
                cerr << "[!] ERROR: Invalid choice." << endl;
                choice = "";
                break;
            }
            if (!isspace(c)) {
                whitespaceStrippedChoice += c;
            }
        }

        cout << endl;
        if (whitespaceStrippedChoice == "1") {
            cout << ">> Mode 1 selected." << endl;
            mode1();
            cout << endl;
        }
        else if (whitespaceStrippedChoice == "2") {
            cout << ">> Mode 2 selected." << endl;
            mode2();
            cout << endl;
        }
    }
}