/*
    Assessment 1 - Challenge 8
    Task: Dynamic Inventory
    
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int INVENTORY_SIZE_LIMIT = 16;

struct InventoryItem {
public:
    void setName(string newName) {
        name = newName;
    }
    string readName() {
        return name;
    }
private:
    string name;
};

// Takes a place inside the inventory - Allows setting up the inventory size and putting items in the inventory in slot 7 when the slots before it are
// empty etc
struct EmptyInventoryItem : InventoryItem {};

vector<InventoryItem> inventory = {};

void initializeInventorySize() {
    int size = 0;
    while (size < 1 || size > INVENTORY_SIZE_LIMIT) {
        cout << " - Please enter your inventory size: ";
        cin >> size;

        if (cin.fail()) {
            cerr << " [!] ERROR: Invalid input. That is not an integer." << endl;
            cin.clear(istream::failbit);
            cin.ignore();
            cin.ignore(INT_MAX, '\n');
        }
        else if (size == 0 || size > INVENTORY_SIZE_LIMIT) {
            cerr << " [!] ERROR: Invalid inventory size. Please choose a size between 1 and " << int(INVENTORY_SIZE_LIMIT) << "." << endl;
        }
    }
    // Clears the cin stream for later use
    cin.ignore();

    cout << " >> Initialized inventory with size " << size << "." << endl;

    for (int i = 0; i < size; i++) {
        EmptyInventoryItem eii;
        inventory.push_back(eii);
    }
}

void viewItem(int index) {

}

void showAll() {

}

void setItem(int index, int itemID) {

}

void searchItem(string str) {

}

void showItems() {

}

void exitTool() {
    exit;
}

void restartSession() {

}

void getHelpInfo() {

}

void clearInventory() {

}

const vector<string> AVAILABLE_COMMANDS = { "view", "show_all", "set", "search_item", "items", "exit", "restart", "help", "clear" };
const vector<string> COMMANDS_WITHOUT_SYNTAX = { "show_all", "items", "exit", "restart", "help", "clear" };
enum CommandExecutionResult {
    COMMAND_COMPLETED,
    COMMAND_FAILED,
    EXIT_PROGRAM,
};

string getFirstWord(string str) {
    string result = "";
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
        else {
            return result;
        }
    }
    return result;
}

string getSyntaxPastFirstWord(string str) {
    string result = "";
    bool onFirstWord = true;
    for (char c : str) {
        if (!onFirstWord) {
            result += c;
            continue;
        }
        if (c == ' ') {
            onFirstWord = false;
        }
    }
    return result;
}

template <typename S, typename A>
bool isWithin(S searching, A structure) {
    for (S s : structure) {
        if (searching == s) {
            return true;
        }
    }
    return false;
}

bool isCommandCorrectSyntax(string input) {
    string command = getFirstWord(input);
    string syntax = getSyntaxPastFirstWord(input);
    if (!isWithin(command, AVAILABLE_COMMANDS)) {
        return false;
    }
    if (isWithin(command, COMMANDS_WITHOUT_SYNTAX)) {
        return true;
    }
    if (syntax == "") {
        return false;
    }

    if (command == "view") {
        bool seenFirstNum = false;
        bool onFirstNum = false;
        for (char c : syntax) {
            if (onFirstNum && c == ' ' && seenFirstNum) {
                onFirstNum = false;
            }
            if (!seenFirstNum && isdigit(c)) {
                seenFirstNum = true;
                onFirstNum = true;
            }
            if (!onFirstNum && isdigit(c)) {
                cout << "Nuh uh" << endl;
                return false;
            }
            if (!isdigit(c) && c != ' ') {
                cout << "Nuh uh" << endl;
                return false;
            }
        }
        int viewNum = stoi(syntax);
        if (viewNum <= 0 || viewNum > INVENTORY_SIZE_LIMIT) {
            return false;
        }
    }
    else if (command == "set") {
        for (char c : syntax) {
            if (!isdigit(c)) {
                cout << "Nuh uh" << endl;
                return false;
            }
        }
        int setIndex;
        int itemID;
    }
    else if (command == "search_item") {
        bool onFirstSyntaxWord = true;
        for (char c : syntax) {
            if (c == ' ') {
                onFirstSyntaxWord = false;
            }
            if (isalnum(c) && !onFirstSyntaxWord) {
                cout << "Nuh uh" << endl;
                return false;
            }
        }
    }
    cout << "Yeh uh" << endl;
    return true;
}

CommandExecutionResult doCommand(string input) {
    if (!isCommandCorrectSyntax(input)) {
        return COMMAND_FAILED;
    }
    string command = getFirstWord(input);
    if (command == "view") {

    }
    else if (command == "show_all") {

    }
    else if (command == "set") {

    }
    else if (command == "search_item") {

    }
    else if (command == "items") {

    }
    else if (command == "exit") {
        return EXIT_PROGRAM;
    }
    else if (command == "restart") {

    }
    else if (command == "help") {

    }
    else if (command == "clear") {

    }
    return COMMAND_COMPLETED;
}

int main(int argc, char* argv[])
{
    string input;
    initializeInventorySize();
    cout << " >> Type 'help' for a list of all commands. Otherwise, please enter a command in lower case only." << endl;
    while (true) {
        input = "";
        do {
            cout << " - ";
            getline(cin, input);
            if (cin.fail()) {
                cerr << " [!] ERROR: Invalid input detected." << endl;
            }
            else {
                if (!isCommandCorrectSyntax(input)) {
                    cerr << " [!] ERROR: Invalid command detected. Incorrect syntax or unknown command. Type 'help' for a list of all commands." << endl;
                    continue;
                }
                CommandExecutionResult commandResult = doCommand(input);
                if (commandResult == COMMAND_FAILED) {
                    cerr << " [!] ERROR: Command failed." << endl;
                }
                else if (commandResult == EXIT_PROGRAM) {
                    return 0;
                }
            }
        } while (input.length() == 0);
    }
}