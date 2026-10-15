/*
    Assessment 1 - Challenge 7
	Task: Party Selection
    
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int partyMemberCount = 3;
vector<string> partyNames;
int startingCoinCount = 100;
int partyCoinCount;

struct ShopItem {
    string itemName;
    string itemType;
    int price;
    int damage;
    string characterRole;
};

map<int, ShopItem> shopItems = {
    {1, ShopItem("Great Sword", "Sword", 40, 100, "Knight")},
    {2, ShopItem("Scimitar", "Sword", 35, 75, "Knight")},
    {3, ShopItem("Dagger", "Sword", 10, 35, "Knight")},
    {4, ShopItem("Longbow", "Bow", 20, 55, "Archer")},
    {5, ShopItem("Crossbow", "Bow", 40, 100, "Archer")},
    {6, ShopItem("Rusty Spear", "Spear", 10, 35, "Spearman")},
    {7, ShopItem("Iron Spear", "Spear", 20, 65, "Spearman")},
};
vector<int> boughtShopItems = {};

map<string, ShopItem> partyItems = {};

vector<string> getPartyNames() {
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
    int itemNum = 1;
    for (const auto& [itemName, shopItem] : shopItems) {
        cout << itemNum << ". " << shopItem.itemName << " [" << shopItem.price << " coins, " 
            << shopItem.damage << " damage]" << endl;
        itemNum++;
    }
    cout << endl;
}

bool letPlayersChooseItems() {
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
        string happyWithPurchases;
        cout << "Are you happy with your selection of weapons? {yes/no}: ";
        getline(cin, happyWithPurchases);

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

    bool allItemsChosen = false;
    while (!allItemsChosen) {
        partyCoinCount = startingCoinCount;
        ouputShopWelcomeMessage();
        outputShopItems();
        allItemsChosen = letPlayersChooseItems();
    }

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