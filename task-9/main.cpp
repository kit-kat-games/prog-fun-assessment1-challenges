/*
    Assessment 1 - Challenge 8
    Task: Dynamic Inventory
    Uses a menu like system to prompt the user for a series of commands to manipulate a dynamic inventory. Allows setting a size for the inventory, setting, viewing and clearing items as well
        as providing proper feedback errors on the issues with any user-inputted feedback.
*/

#include <iostream>
#include <string>
#include <vector>
#include "Vector2.h"
using namespace std;

enum ParseStep {
    PARSESTEP_OPENBRACKET,
    PARSESTEP_FIRSTNUM,
    PARSESTEP_COMMA,
    PARSESTEP_SECONDNUM,
    PARSESTEP_CLOSEBRACKET,
    PARSESTEP_FINISHEDPARTS
};

bool isValidInput(string input) {
    ParseStep parseStep = PARSESTEP_OPENBRACKET;
    string curPart = "";
    char lastC = ' ';

    cout << "CHECKING OPENING BRACKETS" << endl;
    for (char c : input) {
        switch (parseStep) {
        case PARSESTEP_OPENBRACKET:
            // Move to next parse step
            if (c == '[') { parseStep = PARSESTEP_FIRSTNUM; cout << "CHECKING FIRST NUM" << endl; }
            // An invalid character
            if (!isspace(c) && c != '[') { return false; }
            break;
        case PARSESTEP_FIRSTNUM:
            // An invalid character
            if (!isdigit(c) && !isspace(c) && c != '.' && c != ',') { return false; }
            // Two '.' characters in a row
            if (c == '.' && lastC == '.') { return false; }

            
            // Move to next parse step
            if (isspace(c) && curPart != "") { parseStep = PARSESTEP_COMMA; curPart = ""; cout << "CHECKING COMMA" << endl; continue; }
            if (c == ',' && curPart != "") { parseStep = PARSESTEP_SECONDNUM; curPart = ""; cout << "CHECKING SECOND NUM" << endl; continue; }
            curPart += c;
            break;
        case PARSESTEP_COMMA:
            // Move to next parse step
            if (c == ',') { parseStep = PARSESTEP_SECONDNUM; curPart = ""; cout << "CHECKING SECOND NUM" << endl; }
            // An invalid character
            if (!isspace(c) && c != ',') { return false; }
            break;
        case PARSESTEP_SECONDNUM:
            if (lastC != ',' && c == ',') { continue; }
            // An invalid character
            if (!isdigit(c) && !isspace(c) && c != '.' && c != ']') { return false; }
            // Two '.' characters in a row
            if (c == '.' && lastC == '.') { return false; }

            // Move to next parse step
            if (!isdigit(c) && c != '.' && c != ']' && curPart != "") { parseStep = PARSESTEP_CLOSEBRACKET; curPart = ""; cout << "CHECKING CLOSING BRACKET" << endl; continue; }
            if (!isdigit(c) && c == ']' && curPart != "") { parseStep = PARSESTEP_FINISHEDPARTS; curPart = ""; cout << "CHECKING LEFTOVERS" << endl; continue; }
            curPart += c;
            break;
        case PARSESTEP_CLOSEBRACKET:
            cout << c << endl;
            // Move to next parse step
            if (c == ']') { parseStep = PARSESTEP_FINISHEDPARTS; curPart = ""; cout << "CHECKING LEFTOVERS" << endl; }
            // An invalid character
            if (!isspace(c) && c != ']') { return false; }
            break;
        case PARSESTEP_FINISHEDPARTS:
            // Any non-space characters after closed bracket
            if (!isspace(c)) { return false; }
        }
    }
}

Vector2 parseInput(string input) {
    if (!isValidInput(input)) {
        cerr << "ERROR" << endl;
        return Vector2(0, 0);
    }

    ParseStep parseStep = PARSESTEP_OPENBRACKET;
    vector<string> parts = {};
    string curPart = "";
    char lastC = ' ';

    for (char c : input) {
        switch (parseStep) {
        case PARSESTEP_OPENBRACKET:
            // Add to parts. Then move to next parse step
            if (c == '[') { parts.push_back("["); parseStep = PARSESTEP_FIRSTNUM; }
            break;
        case PARSESTEP_FIRSTNUM:
            // Add a 0 to the start of a number. Fe .6 would be 0.6. Then add to cur part to form whole number
            if (c == '.' && curPart == "") { curPart += ("0" + c); }
            // Add to cur part to form whole number
            else if (isdigit(c) || c == '.') { curPart += c; }

            // Add to parts. Then move to next parse step
            if (isspace(c) && curPart != "" && lastC != '.') { parts.push_back(curPart); parseStep = PARSESTEP_COMMA; curPart = ""; }
            // Add a 0 to the end of a number. Fe 5. would be 5.0. Then add to parts. Then move to next parse step
            else if (isspace(c) && curPart != "") { curPart += "0"; parts.push_back(curPart); parseStep = PARSESTEP_COMMA; curPart = ""; }
            if (c == ',' && curPart != "" && lastC != '.') { parts.push_back(curPart); parts.push_back(","); parseStep = PARSESTEP_SECONDNUM; curPart = ""; }
            break;
        case PARSESTEP_COMMA:
            // Add to parts. Then move to next parse step
            if (c == ',') { parts.push_back(","); parseStep = PARSESTEP_SECONDNUM; }
            break;
        case PARSESTEP_SECONDNUM:
            // Add a 0 to the start of a number. Fe .6 would be 0.6. Then add to cur part to form whole number
            if (c == '.' && curPart == "") { curPart += ("0" + c); }
            // Add to cur part to form whole number
            else if (isdigit(c) || c == '.') { curPart += c; }

            // Add to parts. Then move to next parse step
            if ((isspace(c) || c == ',') && curPart != "" && lastC != '.') { parts.push_back(curPart); parts.push_back("]"); parseStep = PARSESTEP_CLOSEBRACKET; continue; }
            // Add a 0 to the end of a number. Fe 5. would be 5.0. Then add to parts. Then move to next parse step
            else if ((isspace(c) || c == ',') && curPart != "") { curPart += "0"; parts.push_back(curPart); parts.push_back("]"); parseStep = PARSESTEP_CLOSEBRACKET; continue; }
            break;
        case PARSESTEP_CLOSEBRACKET:
            continue;
            break;
        }
    }

    for (string s : parts) {
        cout << s << endl;
    }

    return Vector2(0, 0);
}

int main(int argc, char* argv[])
{
    while (true) {
        string input = "";
        cout << "Enter a vector: ";
        getline(cin, input);
        if (cin.fail()) {
            cerr << "ERROR: That is not a string." << endl;
            continue;
        }
        else if (input.empty()) {
            cerr << "ERROR: That is an empty string." << endl;
            continue;
        }
        if (!isValidInput(input)) {
            cerr << "ERROR: That is not a valid vector." << endl;
            continue;
        }
        else {
            parseInput(input);
        }
    }
}

//bool seenOpenBracket = false;
//bool seenX = false;
//bool onX = false;
//bool seenComma = false;
//bool seenY = false;
//bool onY = false;
//bool seenCloseBracket = false;
//char lastC = ' ';
//for (char c : input) {
//    if (!isdigit(c) && c != '[' && c != ']' && c != ' ' && c != ',' && c != '.') {
//        // Seeing any non valid chars. EXAMPLE: [3, 2']
//        return false;
//    }
//    else if (c != ' ' && seenCloseBracket) {
//        // Seen any chars other than spaces after a closed bracket. EXAMPLE: [3, 2].
//        return false;
//    }
//    if (c == '[') {
//        // Seeing two opened brackets. EXAMPLE: [[5, 1] or [5, [3]
//        if (seenOpenBracket) { return false; }
//        // Seeing opened bracket
//        else { seenOpenBracket = true; }
//    }
//    if (isdigit(c)) {
//        // Seeing a number before opening the brackets. EXAMPLE: 1, 3]
//        if (!seenOpenBracket) { return false; }
//        // Going onto first number
//        if (!seenX) { seenX = true; onX = true; }
//        // Two seperate numbers before the comma. EXAMPLE: [1 2, 4]
//        if (seenX && !onX && !seenComma) { return false; }
//        // Going onto second number
//        if (seenComma && !seenY) { seenY = true; onY = true; }
//        // Seeing a third number
//        if (seenX && seenY && !onY) { return false; }
//    }
//    if (!isdigit(c) and c != '.') {
//        // Leaving first number
//        if (onX) { onX = false; }
//        // Leaving second number
//        if (onY) { onY = false; }
//        // Set comma status
//        if (c == ',') { seenComma = true; }
//        // If last seen a '.' and the next char isnt a number. EXAMPLE: [5..1, 3]
//        if (lastC == '.') { return false; }
//    }
//    if (c == '.') {
//        // Seeing a '.' outside of a number, EXAMPLE: [4, . 2]
//        if (!onX || !onY) { return false; }
//        if (!isdigit(lastC)) { return false; }
//    }
//    if (c == ',') {
//        // Seeing a comma within a number. EXAMPLE: [7, 5,4]
//        if (onX || onY) { return false; }
//        // Seeing a comma before the first number [, 3, 2]
//        if (!seenX) { return false; }
//        // Seeing a comma after second number. EXAMPLE: [4, 3,]
//        if (seenY) { return false; }
//    }
//    if (c == ']') {
//        // Seeing closed bracket before seeing either number. EXAMPLE: [5, ]1 or []5, 1 etc
//        if (!seenX || !seenY) { return false; }
//        // Seeing two closed brackets. EXAMPLE: [3, 4]]
//        if (seenCloseBracket) { return false; }
//        // Seeing closed bracket
//        else { seenCloseBracket = true; }
//    }
//    lastC = c;
//}