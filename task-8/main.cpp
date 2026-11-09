/*
    Assessment 1 - Challenge 8
    Task: Dynamic Inventory
    
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <windows.h>
using namespace std;

const int INVENTORY_SIZE_LIMIT = 16;
enum CommandExecutionResult { EXECUTIONRESULT_COMMANDCOMPLETED, EXECUTIONRESULT_COMMANDFAILED };
enum CommandFailReason { FAILREASON_DIDNOTFAIL, FAILREASON_INVALIDITEMID, FAILREASON_INVALIDSLOTINDEX, FAILREASON_INVALIDSYNTAX };
enum CommandFinishRequest { FINISHREQUEST_NA, FINISHREQUEST_RESTARTSESSION, FINISHREQUEST_EXITPROGRAM };
enum CommandSyntaxError { SYNTAXERROR_NA, SYNTAXERROR_INVALIDITEMID, SYNTAXERROR_INVALIDSLOTINDEX, SYNTAXERROR_INVALIDVARCOUNT };
struct CommandResult {
    CommandExecutionResult executionResult;
    CommandFailReason failReason = FAILREASON_DIDNOTFAIL;
    CommandFinishRequest finishRequest = FINISHREQUEST_NA;
};

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

// Pre Defines
void initializeInventorySize();

// Command Deciphering Functions -------------------------------
string getCommand(string str) {
    string result = "";
    for (char c : str) {
        if (c != ' ') {
            result += tolower(c);
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
            result += tolower(c);
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
    return (i >= 0 && i < inventory.size());
}

// Command Functions -------------------------------
void viewItem(int index) {
    if (isWithinInventoryIndexBounds(index)) {
        InventoryItem item = inventory[index];
        int itemID = item.readItemId();
        cout << " >> Inventory Slot " << index << " details:" << endl;
        cout << " >> Name: " << items.at(itemID) << endl;
    }
    else {
        cout << index << endl;
    }
}

void showAll() {
    cout << " >> Inventory: " << endl;
    for (int i = 0; i < inventory.size(); i++) {
        InventoryItem item = inventory[i];
        int itemID = item.readItemId();
        cout << " >> - Slot " << i << ": " << items.at(itemID) << endl;
    }
}

void setItem(int index, int itemID) {
    if (!isWithinInventoryIndexBounds(index)) {
        return;
    }
    if (!items.contains(itemID)) {
        return;
    }
    
    inventory[index].setItemID(itemID);
    cout << " >> Set inventory slot " << index << " to item " << items.at(itemID) << "." << endl;
}

void searchItem(string str) {
    vector<int> findsIndexes = {};
    vector<string> findsStrings = {};

    for (const pair<int, string>& p : items) {
        // Lower string we are searching through - account for caps disparancy
        string itemName = "";
        for (char c : p.second) {
            itemName += tolower(c);
        }
 
        bool containsStr = (itemName.find(str) != string::npos);
        if (containsStr) {
            findsIndexes.push_back(p.first);
            findsStrings.push_back(p.second);
        }
    }

    if (findsIndexes.size() > 0) {
        cout << " >> Search Results: " << endl;
        for (int i = 0; i < findsIndexes.size(); i++) {
            int index = findsIndexes[i];
            string find = findsStrings[i];
            cout << " >> Item Index " << index << ": " << find << endl;
        }
    }
    else {
        cout << " >> No search results found." << endl;
    }
}

void showItems() {
    for (const pair<int, string>& p : items) {
        cout << " >> ID " << p.first << ": " << p.second << endl;
    }
}

void restartSession() {
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

void showHelpInfo() {
    cout << " >> view <index>: Prints out details of the item specified by slot index." << endl;
    cout << " >> show_all: Shows all inventory slots and their details." << endl;
    cout << " >> set <index> <itemid>: Sets slot specified by index to the item given." << endl;
    cout << " >> search_item <str>: Searches the item list for any item with the given name." << endl;
    cout << " >> items: Shows all items." << endl;
    cout << " >> exit: Exits the tool." << endl;
    cout << " >> restart: Restarts the session." << endl;
    cout << " >> help: Shows this list of commands." << endl;
    cout << " >> clear: Clears the inventory." << endl;
}

void clearInventory() {
    cout << " >> Cleared inventory." << endl;
    initializeInventorySize(); 
}

// Session Functions -------------------------------
void initializeInventorySize() {
    if (inventory.size() > 0) {
        inventory.clear();
    }

    int size = 0;
    while (size < 1 || size > INVENTORY_SIZE_LIMIT) {
        cout << " - Please enter your inventory size: ";
        cin >> size;

        if (cin.fail()) {
            cerr << " [!] ERROR: Invalid input. That is not an integer." << endl;
            cin.clear();
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
        if (!isWithinInventoryIndexBounds(viewNum)) {
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

        if (!isWithinInventoryIndexBounds(setIndex)) {
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

CommandResult doCommand(string input) {
    if (!isCommandCorrectSyntax(input)) {
        return CommandResult(EXECUTIONRESULT_COMMANDFAILED, FAILREASON_INVALIDSYNTAX);
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
        return CommandResult(EXECUTIONRESULT_COMMANDCOMPLETED, FAILREASON_DIDNOTFAIL, FINISHREQUEST_EXITPROGRAM);
    }
    else if (command == "restart") {
        return CommandResult(EXECUTIONRESULT_COMMANDCOMPLETED, FAILREASON_DIDNOTFAIL, FINISHREQUEST_RESTARTSESSION);
    }
    else if (command == "help") {
        showHelpInfo();
    }
    else if (command == "clear") {
        clearInventory();
    }
    return CommandResult(EXECUTIONRESULT_COMMANDCOMPLETED);
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
                CommandResult commandResult = doCommand(input);
                if (commandResult.executionResult == EXECUTIONRESULT_COMMANDFAILED) {
                    if (commandResult.failReason == FAILREASON_INVALIDSYNTAX) {
                        cerr << " [!] ERROR: Command failed. Incorrect syntax or unknown command. Type 'help' for a list of all commands." << endl;
                    }
                    else if (commandResult.failReason == FAILREASON_INVALIDITEMID) {
                        cerr << " [!] ERROR: Command failed. Invalid item id chosen." << endl;
                    }
                    else if (commandResult.failReason == FAILREASON_INVALIDSLOTINDEX) {
                        cerr << " [!] ERROR: Command failed. Invalid inventory slot index chosen." << endl;
                    }
                    else {
                        cerr << " [!] ERROR: Command failed." << endl;
                    }
                }
                else if (commandResult.finishRequest == FINISHREQUEST_EXITPROGRAM) {
                    return 0;
                }
                else if (commandResult.finishRequest == FINISHREQUEST_RESTARTSESSION) {
                    restartSession();
                    initializeInventorySize();
                    cout << " >> Type 'help' for a list of all commands. Otherwise, please enter a command in lower case only." << endl;
                }
            }
        } while (input.length() == 0);
    }
}