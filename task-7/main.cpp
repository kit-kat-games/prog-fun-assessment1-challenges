/*
    Assessment 1 - Challenge 7
	Task: Party Selection
    Prompts the user to create a party of 3 adventurers. The user is then prompted to choose and purchase weapons 
        (represented by ShopItem structs), which once completed and confirmed, are outputted with a start message
        for an adventurer
    Uses maps, vectors and a custom struct for different methods of data input, handling and format
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// Models the data shop items need
struct ShopItem {
    string itemName;
    string itemType;
    int price;
    int damage;
    string characterRole;
};

// Party member variables
int partyMemberCount = 3;
vector<string> partyNames;

// Coin variables
int startingCoinCount = 100;
int partyCoinCount;

// Item variables
vector<int> boughtShopItems = {};
map<string, ShopItem> partyItems = {};

// Define the given purchaseable shop items
map<int, ShopItem> shopItems = {
    {1, ShopItem("Great Sword", "Sword", 40, 100, "Knight")},
    {2, ShopItem("Scimitar", "Sword", 35, 75, "Knight")},
    {3, ShopItem("Dagger", "Sword", 10, 35, "Knight")},
    {4, ShopItem("Longbow", "Bow", 20, 55, "Archer")},
    {5, ShopItem("Crossbow", "Bow", 40, 100, "Archer")},
    {6, ShopItem("Rusty Spear", "Spear", 10, 35, "Spearman")},
    {7, ShopItem("Iron Spear", "Spear", 20, 65, "Spearman")},
};

vector<string> getPartyNames() {
    // Prompt user to input names until they enter 3 valid names (can be changed by changing value of partyMemberCount)
    vector<string> names;
    do {
		string name;
        cout << " - Please enter player #" << names.size() + 1 << "'s name: ";
        getline(cin, name);
        if (cin.fail()) {
            cerr << "ERROR: That is not a string." << endl;
        }
        else if (name == "") {
            cerr << "ERROR: That is an empty string." << endl;
        }
        else if (find(names.begin(), names.end(), name) != names.end()) {
            cerr << "ERROR: That name has already been used. Please use a new one." << endl;
        }
        else {
            bool noLetters = true;
            for (char letter : name) {
                if (isalpha(letter)) {
                    noLetters = false;
                }
            }
            if (noLetters) {
                cerr << "ERROR: There are no letters in that name." << endl;
            }
            else {
                names.push_back(name);
            }
        }
    } while (names.size() < partyMemberCount);
    cout << endl;
	return names;  
}

void ouputShopWelcomeMessage() {
    // Formats shop welcome message based on inputted party names
    cout << "Welcome ";
    int namesPrinted = 0;
    for (string name : partyNames) {
        cout << name;
        namesPrinted++;
        if (namesPrinted < partyMemberCount - 1) {
            cout << ", ";
        }
        else if (namesPrinted == partyMemberCount - 1) {
            cout << " and ";
        }
    }
    cout << " to the shop!" << endl;
    cout << "You currently have " << partyCoinCount << " coins. You can buy the following items:" << endl;
}

void outputShopItems() {
    // Format the available items in the shop
    int itemNum = 1;
    for (const auto& [itemName, shopItem] : shopItems) {
        cout << itemNum << ". " << shopItem.itemName << " [" << shopItem.price << " coins, " 
            << shopItem.damage << " damage]" << endl;
        itemNum++;
    }
    cout << endl;
}

bool letPlayersChooseItems() {
    // Have the player input item choices until an item is chosen for each player (accounting for prices, single stock
    // of each item, and handling feedback given to player about purchased weapons
    do {
        int chosenItemNumber = -1;
        cout << "Player " << partyItems.size() + 1 << ", please enter a weapon to buy: ";
        cin >> chosenItemNumber;

        if (cin.fail()) {
            cerr << "ERROR: That is not a number." << endl;
            continue;
        }
        else if (chosenItemNumber < 1 || chosenItemNumber > shopItems.size()) {
            cerr << "ERROR: Please choose a valid item number." << endl;
            continue;
        }

        ShopItem selectedItem = shopItems[chosenItemNumber];

        bool alreadyPurchased = find(boughtShopItems.begin(), boughtShopItems.end(), chosenItemNumber) != boughtShopItems.end();
        if (alreadyPurchased) {
            cerr << "ERROR: That item has already been chosen." << endl;
            continue;
        }
        
        bool haveFunds = selectedItem.price <= partyCoinCount;
        if (!haveFunds) {
            cerr << "ERROR: You do not have enough coins for that item." << endl;
            continue;
        }
        
        // Register item as already purchased - Cannot be bought again
        boughtShopItems.push_back(chosenItemNumber);
        
        // Takes coins for the item and records the purchase for the users
        partyCoinCount -= shopItems[chosenItemNumber].price;
        cout << partyNames[partyItems.size()] << " bought a " << selectedItem.itemName
            << " for " << selectedItem.price << " coins. The party has " << partyCoinCount
            << " coins." << endl << endl;

        // Store item and player name for later access
        partyItems.insert_or_assign(partyNames[partyItems.size()], selectedItem);
        

    } while (partyItems.size() < partyMemberCount);
    
    while (true) {
        string input;
        string happyWithPurchases;
        cout << "Are you happy with your selection of weapons? {yes/no}: ";
        // cin >> ws prevents duplication issues with how cin works
        getline(cin >> ws, input);

        for (char letter : input) {
            happyWithPurchases += tolower(letter);
        }

        if (happyWithPurchases == "yes") {
            return true;
        }
        else if (happyWithPurchases == "no") {
            return false;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    partyNames = getPartyNames();

    // Have the user purchase different items from the shop until they are happy with their purchases
    bool allItemsChosen = false;
    while (!allItemsChosen) {
        partyCoinCount = startingCoinCount;
        ouputShopWelcomeMessage();
        outputShopItems();
        allItemsChosen = letPlayersChooseItems();
    }

    cout << endl;
    cout << "The party:" << endl;
    for (int i = 0; i < partyNames.size(); i++) {
        string player = partyNames[i];
        ShopItem playerItem = partyItems[player];
        cout << "Player " << i + 1 << " (" << player << "), "
            << "Role: " << playerItem.characterRole << ", "
            << "Weapon: " << playerItem.itemName << ", "
            << "Damage: " << playerItem.damage << "." << endl;
    }

    cout << endl;
    cout << "You are situated in a forest. A monster appears...";
}