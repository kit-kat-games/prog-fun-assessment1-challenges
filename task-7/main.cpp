/*
    Assessment 1 - Challenge 7
	Task: Party Selection
    
*/

#include <iostream>
#include <list>
#include <string>
#include <map>
using namespace std;

int partyMemberNum = 3;
list<string> partyNames;
int startingCoinCount = 100;
int partyCoinCount;

struct ShopItem {
    string itemName;
    string itemType;
    int price;
    int damage;
    string characterRole;
    /*ShopItem(string _itemName, string _itemType, int _price, int _damage, string _characterRole) {
        itemName = _itemName;
        itemType = _itemType;
        price = _price;
        damage = _damage;
        characterRole = _characterRole;
    }*/
};

map<string, ShopItem> shopItems = {
    {"Great Sword", ShopItem("Great Sword", "Sword", 40, 100, "Knight")},
    {"Scimitar", ShopItem("Scimitar", "Sword", 35, 75, "Knight")},
    {"Dagger", ShopItem("Dagger", "Sword", 10, 35, "Knight")},
    {"Longbow", ShopItem("Longbow", "Bow", 20, 55, "Archer")},
    {"Crossbow", ShopItem("Crossbow", "Bow", 40, 100, "Archer")},
    {"Rusty Spear", ShopItem("Rusty Spear", "Spear", 10, 35, "Spearman")},
    {"Iron Spear", ShopItem("Iron Spear", "Spear", 20, 65, "Spearman")},
};

list<string> getPartyNames() {
    list<string> names;
    
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
    } while (names.size() < partyMemberNum);

	return names;  
}

void ouputShopWelcomeMessage() {
    cout << "Welcome ";
    int namesPrinted = 0;
    for (string name : partyNames) {
        cout << name;
        namesPrinted++;
        if (namesPrinted < partyMemberNum - 1) {
            cout << ", ";
        }
        else if (namesPrinted == partyMemberNum - 1) {
            cout << " and ";
        }
    }
    cout << " to the shop!" << endl;
    cout << "You currently have " << partyCoinCount << " coins. You can buy the following items:" << endl;
}

bool outputShopItems() {
    int itemNum = 1;
    for (const auto& [itemName, shopItem] : shopItems) {
        cout << itemNum << ". " << shopItem.itemName << " [" << shopItem.price << " coins, " << shopItem.damage << " damage]" << endl;
        itemNum++;
    }

    return true;
}


int main(int argc, char* argv[])
{
    partyNames = getPartyNames();

    bool allItemsChosen = false;
    while (!allItemsChosen) {
        partyCoinCount = startingCoinCount;
        ouputShopWelcomeMessage();
        allItemsChosen = outputShopItems();
    }
}