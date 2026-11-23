/*
    Assessment 1 - Challenge 8
    Task: Dynamic Inventory
    Uses a menu like system to prompt the user for a series of commands to manipulate a dynamic inventory. Allows setting a size for the inventory, setting, viewing and clearing items as well
        as providing proper feedback errors on the issues with any user-inputted feedback.
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
enum CommandSyntaxError { SYNTAXERROR_NA, SYNTAXERROR_INVALIDITEMID, SYNTAXERROR_INVALIDSLOTINDEX, SYNTAXERROR_INVALIDCOMMAND, SYNTAXERROR_INVALIDVARCOUNT, SYNTAXERROR_INVALIDVARTYPE };
struct CommandResult {
    CommandExecutionResult executionResult;
    CommandFailReason failReason = FAILREASON_DIDNOTFAIL;
    CommandFinishRequest finishRequest = FINISHREQUEST_NA;
};
struct SyntaxResult {
    bool validSyntax;
    CommandSyntaxError syntaxError = SYNTAXERROR_NA;
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
        if (!isspace(c)) {
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
        if (isspace(c)) {
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
        if (!isspace(c) && !seenAVar) {
            seenAVar = true;
        }
        if (isspace(lastC) && c != lastC && seenAVar) {
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
        if (!isspace(c) && !seenXthWord[x]) {
            seenXthWord[x] = true;
            onXthWord[x] = true;
        }
        if (!isspace(c) && onXthWord[x]) {
            result[x] += c;
        }
        if (isspace(c) && onXthWord[x]) {
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
    cout << " >> Type 'help' for a list of all commands. Otherwise, please enter a command in lower case only." << endl;
}

// Session Functions -------------------------------
void initializeInventorySize() {
    if (inventory.size() > 0) {
        inventory.clear();
    }

    int size = 0;
    string input;
    do {
        bool validInput = true;
        cout << " - Please enter your inventory size: ";
        getline(cin, input);

        bool seenMinusSign = false; bool seenNum = false; bool onNum = false;
        // Checks that there is a single integer value within the string, with availability for spaces before
        // and after the number
        for (char c : input) {
            // If already proven invalid, do not need to check any further characters
            if (!validInput) { continue; }
            // If any invalid characters within
            else if (!isdigit(c) && !isspace(c) && c != '-') { validInput = false; }
            // If any digits present after the number finishes
            else if (isdigit(c) && seenNum && !onNum) { validInput = false; }
            // If multiple minus signs present
            else if (c == '-' && seenMinusSign) { validInput = false; }
            // If a minus sign present anywhere after the start of the num
            else if (c == '-' && seenNum) { validInput = false; }
            // If there is a space between a minus sign and the number
            else if (isspace(c) && seenMinusSign && !seenNum) { validInput = false; }

            // Seeing a valid minus sign
            else if (c == '-' && !seenMinusSign && !seenNum) { seenMinusSign = true; }
            // Entering the start of the number
            else if (isdigit(c) && !seenNum) { seenNum = true; onNum = true; }
            // Leaving the end of the number
            else if (isspace(c) && onNum) { onNum = false; }
        }

        if (!validInput || !seenNum) {
            cerr << " [!] ERROR: Invalid input. That is not an integer." << endl;
            input = "";
        }
        else {
            string numString;
            for (char c : input) {
                if (isdigit(c)) { 
                    numString += c; 
                }
            }
            size = stoi(numString);
            if (seenMinusSign) { 
                size *= -1; 
            }
            if (size < 1 || size > INVENTORY_SIZE_LIMIT) {
                cerr << " [!] ERROR: Invalid inventory size. Please choose a size between 1 and " << int(INVENTORY_SIZE_LIMIT) << "." << endl;
                input = "";
            }
        }
    } while (input == "");

    cout << " >> Initialized inventory with size " << size << "." << endl;

    for (int i = 0; i < size; i++) {
        InventoryItem emptyItem;
        inventory.push_back(emptyItem);
    }
}

SyntaxResult isCommandCorrectSyntax(string input) {
    string command = getCommand(input);
    string syntax = getSyntax(input);
    if (!isWithin(command, AVAILABLE_COMMANDS)) {
        return SyntaxResult(false, SYNTAXERROR_INVALIDCOMMAND);
    }
    if (isWithin(command, COMMANDS_WITHOUT_SYNTAX)) {
        return SyntaxResult(true);
    }
    if (syntax == "") {
        return SyntaxResult(false, SYNTAXERROR_INVALIDVARCOUNT);
    }

    if (command == "view") {
        for (char c : syntax) {
            if (!isdigit(c) && !isspace(c)) {
                return SyntaxResult(false, SYNTAXERROR_INVALIDVARTYPE);
            }
        }

        int syntaxVarCount = countSyntaxVars(syntax);
        if (syntaxVarCount != 1) {
            return SyntaxResult(false);
        }
        vector<string> syntaxVars = splitSyntaxVars(syntax, 1);
        int viewNum = stoi(syntaxVars[0]);
        if (!isWithinInventoryIndexBounds(viewNum)) {
            return SyntaxResult(false, SYNTAXERROR_INVALIDSLOTINDEX);
        }
    }
    else if (command == "set") {
        for (char c : syntax) {
            if (!isdigit(c) && !isspace(c)) {
                return SyntaxResult(false, SYNTAXERROR_INVALIDVARTYPE);
            }
        }

        int syntaxVarCount = countSyntaxVars(syntax);
        if (syntaxVarCount != 2) {
            return SyntaxResult(false, SYNTAXERROR_INVALIDVARCOUNT);
        }

        vector<string> syntaxVars = splitSyntaxVars(syntax, 2);
        string setIndexStr = syntaxVars[0];
        string itemIDStr = syntaxVars[1];
        int setIndex = stoi(setIndexStr);
        int itemID = stoi(itemIDStr);

        if (!isWithinInventoryIndexBounds(setIndex)) {
            return SyntaxResult(false, SYNTAXERROR_INVALIDSLOTINDEX);
        }
        if (!items.contains(itemID)) {
            return SyntaxResult(false, SYNTAXERROR_INVALIDITEMID);
        }
    }
    else if (command == "search_item") {
        int syntaxVarCount = countSyntaxVars(syntax);
        if (syntaxVarCount != 1) {
            return SyntaxResult(false, SYNTAXERROR_INVALIDVARCOUNT);
        }
    }
    return SyntaxResult(true);
}

void printSyntaxError(CommandSyntaxError syntaxError) {
    switch (syntaxError) {
    case SYNTAXERROR_INVALIDCOMMAND:
        cerr << " [!] ERROR: Invalid command." << endl;
        break;
    case SYNTAXERROR_INVALIDITEMID:
        cerr << " [!] ERROR: Invalid item index." << endl;
        break;
    case SYNTAXERROR_INVALIDSLOTINDEX:
        cerr << " [!] ERROR: Invalid slot index." << endl;
        break;
    case SYNTAXERROR_INVALIDVARCOUNT:
        cerr << " [!] ERROR: Invalid number of variables." << endl;
        break;
    case SYNTAXERROR_INVALIDVARTYPE:
        cerr << " [!] ERROR: Invalid datatypes of variables." << endl;
        break;
    }
}

CommandResult doCommand(string input) {
    SyntaxResult syntaxResult = isCommandCorrectSyntax(input);
    if (!syntaxResult.validSyntax) {
        printSyntaxError(syntaxResult.syntaxError);
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
                SyntaxResult syntaxResult = isCommandCorrectSyntax(input);
                if (!syntaxResult.validSyntax) {
                    printSyntaxError(syntaxResult.syntaxError);
                    continue;
                }
                CommandResult commandResult = doCommand(input);
                if (commandResult.executionResult == EXECUTIONRESULT_COMMANDFAILED) {
                    if (commandResult.failReason == FAILREASON_INVALIDITEMID) {
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