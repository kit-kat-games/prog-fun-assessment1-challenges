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
    unsigned int playerXPPoints;


    // Request and recieve data
    cout << "Please enter your name: ";
    getline(cin, playerName);

    cout << "Please enter your username: ";
    getline(cin, playerUsername);

    cout << "Please enter your clan tag: ";
    getline(cin, playerClanTag);

    cout << "Please enter your current experience points: ";
    cin >> playerXPPoints;


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