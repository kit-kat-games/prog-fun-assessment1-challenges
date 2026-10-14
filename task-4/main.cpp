/*
    Assessment 1 - Challenge 4
    Task: Text Boxes
    Uses std::cin and iterating in order to produce an ASCII box art with the inputted text as 
        its contents
*/

#include <iostream>
#include <string>

using namespace std;

void doASCIIBoxArt() {
    string inputtedText;

    // Prompt user to input text - Do while loop means it will always be run once, and will only continue
    // running should the condition remain true at the end of the loop
    // In this case, we do not allow the user to stop inputting text until they enter a valid expected
    // string
    do {
        cout << " - Please enter some text: ";
        // Must use getline as otherwise, should the operator simply press enter, cin will enter an
        // error state where further reads will not be valid and will not occur - This is the simplest
        // way to avoid this
        getline(cin, inputtedText);
        if (cin.fail()) {
            cerr << "ERROR: That is not a string." << endl;
        }
        else if (inputtedText.empty()) {
            cerr << "ERROR: That is an empty string." << endl;
        }
    } while (inputtedText == "");

    // Abstracting and representing the line and string data for better in program formatting
    string alternatingString = "=-=-=";
    char connectingChar = '+';
    char pipeChar = '|';
    string topbottomLines;
    string centerLine;

    // Format the top and bottom lines like this '+=-=-=+=-=-=+" with a connecting link for each letter
    for (char letter : inputtedText) {
        topbottomLines = topbottomLines + connectingChar + alternatingString;
    }
    topbottomLines += connectingChar;

    // Format the center line, with pipe (|) symbols seperating the letters
    for (char letter : inputtedText) {
        centerLine = centerLine + pipeChar + "  " + letter + "  ";
    }
    centerLine += pipeChar;

    // Output the properly formatted lines for the ASCII box art
    cout << topbottomLines << endl;
    cout << centerLine << endl;
    cout << topbottomLines << endl;
}

int main(int argc, char* argv[])
{
    // Have the operator create box arts until they close the program
    while (true) {
        doASCIIBoxArt();
    }
}