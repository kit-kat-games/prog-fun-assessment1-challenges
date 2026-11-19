/*
    Assessment 1 - Challenge 2
    Task: Player Details
    Uses std::cin to prompt the user for their details, and format these in returned std::cout statements
*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    // Data we are going to prompt for and format out
    string playerName;
    string playerUsername;
    string playerClanTag;
    unsigned int playerXPPoints = -1;

    // Request and recieve data for each of the user details

    do {
        // Promput user for data
        cout << "Please enter your name: ";
        // Take input from user
        getline(cin, playerName);
        // If empty string, give error message
        if (playerName == "") { cout << "Please enter a non-empty string." << endl; continue; }
        // Check each character, if any are not a space, allow the input.
        bool noNonSpaceChars = true;
        for (char c : playerName) { if (!isspace(c)) { noNonSpaceChars = false; } }
        // If all the characters are spaces, give error message
        if (noNonSpaceChars) {
            cout << "Please enter a string with at least 1 non-space character." << endl;
            playerName = "";
        }
        // Repeat until valid input given
    } while (playerName == "");
    

    do {
        cout << "Please enter your username: ";
        getline(cin, playerUsername);
        if (playerUsername == "") { cout << "Please enter a non-empty string." << endl; continue; }
        bool noNonSpaceChars = true;
        for (char c : playerUsername) { if (!isspace(c)) { noNonSpaceChars = false; } }
        if (noNonSpaceChars) {
            cout << "Please enter a string with at least 1 non-space character." << endl;
            playerUsername = "";
        }
    } while (playerUsername == "");


    do {
        cout << "Please enter your clan tag: ";
        getline(cin, playerClanTag);
        if (playerClanTag == "") { cout << "Please enter a non-empty string." << endl; continue; }
        bool noNonSpaceChars = true;
        for (char c : playerClanTag) { if (!isspace(c)) { noNonSpaceChars = false; } }
        if (noNonSpaceChars) {
            cout << "Please enter a string with at least 1 non-space character." << endl;
            playerClanTag = "";
        }
    } while (playerClanTag == "");


    string input;
    do {
        bool validInput = true;
        cout << "Please enter your current experience points: ";
        getline(cin, input);

        bool seenNum = false; bool onNum = false;
        // Checks that there is a single integer value within the string, with availability for spaces before
        // and after the number
        for (char c : input) {
            // If already proven invalid, do not need to check any further characters
            if (!validInput) { continue; }
            // If any invalid characters within
            else if (!isdigit(c) && !isspace(c)) { validInput = false; }
            // If any digits present after the number finishes
            else if (isdigit(c) && seenNum && !onNum) { validInput = false; }

            // Entering the start of the number
            else if (isdigit(c) && !seenNum) { seenNum = true; onNum = true; }
            // Leaving the end of the number
            else if (isspace(c) && onNum) { onNum = false; }
        }
        
        if (!validInput || !seenNum) { 
            cout << "Please enter a single integer." << endl;
            input = "";
        }
        else {
            string numString;
            for (char c : input) {
                if (isdigit(c)) { numString += c; }
            }
            playerXPPoints = stoi(numString);
        }
    } while (input == "");


    // Calculate further data from recieved values
    int xpPerLevel = 100;
    int currentLevel = playerXPPoints / xpPerLevel;
    int reqExpPoints = (currentLevel + 1) * xpPerLevel - playerXPPoints;


    // Output data in expected format
    cout << "Your name is " << playerName << " and your in-game name is [" 
         << playerClanTag << "]" << playerUsername << "." << endl;
    cout << "You have " << playerXPPoints << " experience points." << endl;
    cout << "Your current level is " << currentLevel << "." << endl;
    cout << "You need " << reqExpPoints << " points to reach the next level, which is level " 
         << currentLevel + 1 << "." << endl;
}