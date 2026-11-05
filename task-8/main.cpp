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
enum CommandExecutionResult { COMMAND_COMPLETED, COMMAND_FAILED, EXIT_PROGRAM };

struct InventoryItem {
public:
    void clearItem() {
        itemID = 0; // Empty item slot
    }
    void setItemID(int newItemID) {
        itemID = newItemID;
    }
    int readItemId() {
        return itemID;
    }
    InventoryItem(int newItemID = 0) {
        itemID = newItemID;
    }
private:
    int itemID;
};

const vector<string> AVAILABLE_COMMANDS = { "view", "show_all", "set", "search_item", "items", "exit", "restart", "help", "clear" };
const vector<string> COMMANDS_WITHOUT_SYNTAX = { "show_all", "items", "exit", "restart", "help", "clear" };
const map<int, string> items = {
    { 0, "Empty" },
    { 1, "Shield" },
    { 2, "Potion" },
    { 3, "Gloves" },
};

vector<InventoryItem> inventory = {};

template <typename S, typename A>
bool isWithin(S searching, A structure) {
    for (S s : structure) {
        if (searching == s) {
            return true;
        }
    }
    return false;
}

// Command Deciphering Functions -------------------------------
string getCommand(string str) {
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

string getSyntax(string str) {
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

int countSyntaxVars(string syntax) {
    int count = 0;
    char lastC = ' ';
    bool seenAVar = false;
    for (char c : syntax) {
        if (c != ' ' && !seenAVar) {
            seenAVar = true;
        }
        if (lastC == ' ' && c != lastC && seenAVar) {
            count++;
        }
        lastC = c;
    }
    return count;
}

vector<string> splitSyntaxVars(string syntax, int expectedSyntaxCount) {
    vector<string> result = {};
    vector<bool> seenXthWord = {};
    vector<bool> onXthWord = {};
    for (int i = 0; i < expectedSyntaxCount; i++) {
        result.push_back("");
        seenXthWord.push_back(false);
        onXthWord.push_back(false);
    }

    int x = 0;
    for (char c : syntax) {
        if (c != ' ' && !seenXthWord[x]) {
            seenXthWord[x] = true;
            onXthWord[x] = true;
        }
        if (c != ' ' && onXthWord[x]) {
            result[x] += c;
        }
        if (c == ' ' && onXthWord[x]) {
            onXthWord[x] = false;
            if (x == expectedSyntaxCount - 1) {
                return result;
            }
            else {
                x++;
            }
        }
    }
}

bool isWithinInventoryIndexBounds(int i) {
    return (i < 0 && i >= inventory.size());
}

// Command Functions -------------------------------
void viewItem(int index) {
    if (isWithinInventoryIndexBounds(index)) {
        InventoryItem item = inventory[index];
        int itemID = item.readItemId();
        cout << " >> Inventory Slot " << index << " details:" << endl;
        cout << " >> Name: " << items.at(itemID) << endl;
    }
}

void showAll() {
    cout << " >> Inventory: " << endl;
    for (int i = 0; i < inventory.size(); i++) {
        InventoryItem item = inventory[i];
        int itemID = item.readItemId();
        cout << " >> - Slot " << i << ": " << itemID << endl;
    }
}

void setItem(int index, int itemID) {

}

void searchItem(string str) {

}

void showItems() {

}

void restartSession() {

}

void showHelpInfo() {

}

void clearInventory() {

}

// Session Functions -------------------------------
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
        InventoryItem emptyItem;
        inventory.push_back(emptyItem);
    }
}

bool isCommandCorrectSyntax(string input) {
    string command = getCommand(input);
    string syntax = getSyntax(input);
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
        for (char c : syntax) {
            if (!isdigit(c) && c != ' ') {
                return false;
            }
        }

        int syntaxVarCount = countSyntaxVars(syntax);
        if (syntaxVarCount != 1) {
            return false;
        }
        vector<string> syntaxVars = splitSyntaxVars(syntax, 1);
        int viewNum = stoi(syntaxVars[0]);
        if (isWithinInventoryIndexBounds(viewNum)) {
            return false;
        }
    }
    else if (command == "set") {
        for (char c : syntax) {
            if (!isdigit(c) && c != ' ') {
                return false;
            }
        }

        int syntaxVarCount = countSyntaxVars(syntax);
        if (syntaxVarCount != 2) {
            return false;
        }

        vector<string> syntaxVars = splitSyntaxVars(syntax, 2);
        string setIndexStr = syntaxVars[0];
        string itemIDStr = syntaxVars[1];
        int setIndex = stoi(setIndexStr);
        int itemID = stoi(itemIDStr);

        if (isWithinInventoryIndexBounds(setIndex)) {
            return false;
        }
        if (!items.contains(itemID)) {
            return false;
        }
    }
    else if (command == "search_item") {
        int syntaxVarCount = countSyntaxVars(syntax);
        if (syntaxVarCount != 1) {
            return false;
        }
    }
    return true;
}

CommandExecutionResult doCommand(string input) {
    if (!isCommandCorrectSyntax(input)) {
        return COMMAND_FAILED;
    }

    string command = getCommand(input);
    string syntax = getSyntax(input);

    if (command == "view") {
        vector<string> syntaxVars = splitSyntaxVars(syntax, 1);
        int viewNum = stoi(syntaxVars[0]);

        viewItem(viewNum);
    }
    else if (command == "show_all") {
        showAll();
    }
    else if (command == "set") {
        vector<string> syntaxVars = splitSyntaxVars(syntax, 2);
        string setIndexStr = syntaxVars[0];
        string itemIDStr = syntaxVars[1];
        int setIndex = stoi(setIndexStr);
        int itemID = stoi(itemIDStr);
        setItem(setIndex, itemID);
    }
    else if (command == "search_item") {
        vector<string> syntaxVars = splitSyntaxVars(syntax, 1);
        string searchStr = syntaxVars[0];
        searchItem(searchStr);
    }
    else if (command == "items") {
        showItems();
    }
    else if (command == "exit") {
        return EXIT_PROGRAM;
    }
    else if (command == "restart") {
        restartSession();
    }
    else if (command == "help") {
        showHelpInfo();
    }
    else if (command == "clear") {
        clearInventory();
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
                    cout << "Nuh uh" << endl;
                    cerr << " [!] ERROR: Invalid command detected. Incorrect syntax or unknown command. Type 'help' for a list of all commands." << endl;
                    continue;
                }
                cout << "Yuh uh" << endl;
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