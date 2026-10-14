/*
    Assessment 1 - Challenge 5
    Task: Text Casing
    Uses different string based manipulation methods to output an inputted sentence in different cases
*/

#include <iostream>
#include <string>
using namespace std;

void doTextCasing() {
    string inputtedText;

    // Prompt the operator for a sentence to text-case
    do {
        cout << " - Please enter some text: ";
        getline(cin, inputtedText);
        if (cin.fail()) {
            cerr << "ERROR: That is not a string." << endl;
        }
        else if (inputtedText.empty()) {
            cerr << "ERROR: That is an empty string." << endl;
        }
        else {
            bool noAlphabetical = true;
            for (char letter : inputtedText) {
                if (isalpha(letter)) {
                    noAlphabetical = false;
                }
            }
            if (noAlphabetical) {
                cerr << "ERROR: Can't run text casing, there is no alphabetical characters in the input string." << endl;
                inputtedText = "";
            }
        }
    } while (inputtedText == "");


    // Create text-cased sentences in the four styles
    string upperCaseText;
    for (char letter : inputtedText) {
        upperCaseText += toupper(letter);
    }

    string lowerCaseText;
    for (char letter : inputtedText) {
        lowerCaseText += tolower(letter);
    }

    string sentenceCaseText;
    bool isFirstCharacter = true;
    for (char letter : inputtedText) {
        if (isFirstCharacter && letter != ' ') {
            sentenceCaseText += toupper(letter);
            isFirstCharacter = false;
        }
        else {
            sentenceCaseText += tolower(letter);
        }

        if (letter == '.' || letter == '?' || letter == '!') {
            isFirstCharacter = true;
        }
    }

    string alternateCaseText;
    bool upperCase = true;
    for (char letter : inputtedText) {
        if (!isalnum(letter)) {
            alternateCaseText += letter;
        }
        else if (upperCase) {
            alternateCaseText += toupper(letter);
            upperCase = false;
        }
        else {
            alternateCaseText += tolower(letter);
            upperCase = true;
        }
    }


    // Output the text-cased sentences
    cout << "Uppercase: " << upperCaseText << endl;
    cout << "Lowercase: " << lowerCaseText << endl;
    cout << "Sentence Casing: " << sentenceCaseText << endl;
    cout << "Alternate Casing: " << alternateCaseText << endl;
}

int main(int argc, char* argv[])
{
    while (true) {
        doTextCasing();  
    }
}