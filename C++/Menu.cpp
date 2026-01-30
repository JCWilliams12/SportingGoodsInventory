#include "Menu.h"
#include <iostream>
#include <limits>   
#include <iomanip>  
#include <cstdlib>  

// Constructor
Menu::Menu() {
    // "new" to store as pointers
    currentInventory.push_back(new VolleyballItem("Pro Net", 10, 50.0, "Professional"));
    currentInventory.push_back(new CampingItem("Everest Tent", 5, 120.0, "4-Season"));
}

// Destructor
Menu::~Menu() {
    for (Item* item : currentInventory) {
        delete item;
    }
    currentInventory.clear();
}

void Menu::clearTerminal() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Clears the input buffer to prevent skipping lines
void Menu::invalidInput() {
    std::cout << "\n!!! Invalid Input. Please try again. !!!\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

//-=--=-=-=-=-=-edit item-=-=-=-=-=-=-
//universal for all item types
void Menu::editItemScreen(Item* item) {
    while (true) {
        clearTerminal();
        std::cout << "--- Editing Item: " << item->itemName << " ---\n";
        std::cout << "[1] Quantity: " << item->quantity << "\n";
        std::cout << "[2] Price:    $" << std::fixed << std::setprecision(2) << item->getPrice() << "\n";
        std::cout << "[3] Discount: " << (int)(item->discount * 100) << "%\n";

        // Dynamic Cast checks if 'item' is a specific child class
        VolleyballItem* v = dynamic_cast<VolleyballItem*>(item);
        TableTennisItem* t = dynamic_cast<TableTennisItem*>(item);
        CampingItem* c = dynamic_cast<CampingItem*>(item);
        SoccerItem* s = dynamic_cast<SoccerItem*>(item);

        // Display specific fields based on type
        if (v) std::cout << "[5] Type:     " << v->trainingType << "\n";
        if (t) {
            std::cout << "[5] Style:    " << t->style << "\n";
            std::cout << "[6] Material: " << t->material << "\n";
        }
        if (c) std::cout << "[5] Rating:   " << c->weatherRating << "\n";
        if (s) std::cout << "[5] Size:     " << s->size << "\n";

        std::cout << "[4] Back\n";
        std::cout << "\nSelect field to edit: ";

        int choice;
        if (!(std::cin >> choice)) {
            invalidInput();
            continue;
        }

        if (choice == 4) break;

        // Handle Standard Edits
        if (choice == 1) {
             std::cout << "Enter new quantity: ";
             std::cin >> item->quantity;
        } else if (choice == 2) {
             std::cout << "Enter new price: ";
             double tempPrice;
             std::cin >> tempPrice;
             item->setPrice(tempPrice);
        } else if (choice == 3) {
             std::cout << "Enter discount percentage (0-100): ";
             double d;
             std::cin >> d;
             item->discount = d / 100.0;
        } 
        // Handle Specific Edits
        else if (choice == 5) {
            std::cout << "Enter new value: ";
            std::cin.ignore(); 
            std::string val;
            std::getline(std::cin, val);
            
            if (v) v->trainingType = val;
            else if (t) t->style = val;
            else if (c) c->weatherRating = val;
            else if (s) s->size = val;
        }
        else if (choice == 6 && t) {
            std::cout << "Enter new material: ";
            std::cin.ignore();
            std::string val;
            std::getline(std::cin, val);
            t->material = val;
        }
        else {
            invalidInput();
        }
    }
}

// =-=-=-=-=-=-=-View Item-=-=-=-=-=-=
//iniversal for all subclasses
void Menu::displayFilteredItems(std::string dept, std::string sect) {
    while (true) {
        clearTerminal();
        std::cout << "--- Inventory: " << dept << " | " << sect << " ---\n";
        
        // Table Header
        //used gemini for formatting
        std::cout << std::left << std::setw(3) << "#" 
                  << std::setw(15) << "Name" 
                  << std::setw(6) << "Qty" 
                  << std::setw(9) << "Price" 
                  << "Details\n";
        std::cout << std::string(75, '-') << "\n";

        std::vector<Item*> matches;
        int index = 1;

        // Filter items
        for (Item* item : currentInventory) {
            if (item->department == dept && item->section == sect) {
                std::cout << "[" << index << "] " << item->getDetails() << "\n";
                matches.push_back(item);
                index++;
            }
        }

        if (matches.empty()) {
            std::cout << "No items found in this section.\n";
            std::cout << "\n[B] Back\n>> ";
            char c; std::cin >> c;
            break;
        }

        std::cout << "\n[#] Enter item number to Edit | [0] Back\n>> ";
        int choice;
        // Check for integer input
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string dummy; 
            std::getline(std::cin, dummy);
            if (dummy == "b" || dummy == "B") break;
            invalidInput();
            continue;
        }

        if (choice == 0) break;
        
        if (choice > 0 && choice <= (int)matches.size()) {
            editItemScreen(matches[choice - 1]);
        } else {
            invalidInput();
        }
    }
}


// -=-=-=-=-=-=-Add Item-=-=-=-=-=-=-=-
void Menu::displayAddItemScreen() {
    clearTerminal();
    std::cout << "--- Add New Item ---\n";
    
    // Clear buffer to ensure getline works
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name;
    std::cout << "Item Name: ";
    std::getline(std::cin, name);

    int qty;
    std::cout << "Quantity: ";
    if (!(std::cin >> qty)) { invalidInput(); return; }

    double price;
    std::cout << "Price: ";
    if (!(std::cin >> price)) { invalidInput(); return; }

    std::cout << "\nSelect Category:\n";
    std::cout << "[1] Volleyball (Indoor)\n";
    std::cout << "[2] Table Tennis (Indoor)\n";
    std::cout << "[3] Camping (Outdoor)\n";
    std::cout << "[4] Soccer (Outdoor)\n>> ";

    int catChoice;
    std::cin >> catChoice;
    //eat new line
    std::cin.ignore();

    Item* newItem = nullptr;

    if (catChoice == 1) {
        std::string tType;
        std::cout << "Type (Training/Professional): ";
        std::getline(std::cin, tType);
        newItem = new VolleyballItem(name, qty, price, tType);
    } else if (catChoice == 2) {
        std::string style, material;
        std::cout << "Style: ";
        std::getline(std::cin, style);
        std::cout << "Material: ";
        std::getline(std::cin, material);
        newItem = new TableTennisItem(name, qty, price, style, material);
    } else if (catChoice == 3) {
        std::string wx;
        std::cout << "Weather Rating: ";
        std::getline(std::cin, wx);
        newItem = new CampingItem(name, qty, price, wx);
    } else if (catChoice == 4) {
        std::string size;
        std::cout << "Size: ";
        std::getline(std::cin, size);
        newItem = new SoccerItem(name, qty, price, size);
    } else {
        std::cout << "Invalid Category.\n";
        return;
    }

    if (newItem) {
        currentInventory.push_back(newItem);
        std::cout << "\nItem added successfully!\n";
        std::cout << "Press Enter to continue...";
        std::cin.get();
    }
}


// -=-=-=-=-=-=-=Navigastion-=-=-=-=-=-=-
void Menu::displayIndoorDepartment() {
    while (true) {
        clearTerminal();
        std::cout << "Indoor Dept\n[1] Volleyball\n[2] Table Tennis\n[3] Back\n>> ";
        int res;
        if (!(std::cin >> res)) { invalidInput(); continue; }

        if (res == 1) displayFilteredItems("indoor", "volleyball");
        else if (res == 2) displayFilteredItems("indoor", "table_tennis");
        else if (res == 3) break;
        else invalidInput();
    }
}

void Menu::displayOutdoorDepartment() {
    while (true) {
        clearTerminal();
        std::cout << "Outdoor Dept\n[1] Camping\n[2] Soccer\n[3] Back\n>> ";
        int res;
        if (!(std::cin >> res)) { invalidInput(); continue; }

        if (res == 1) displayFilteredItems("outdoor", "camping");
        else if (res == 2) displayFilteredItems("outdoor", "soccer");
        else if (res == 3) break;
        else invalidInput();
    }
}

void Menu::displayItemDetailsScreen() {
    while (true) {
        clearTerminal();
        std::cout << "Select Department\n[1] Indoor\n[2] Outdoor\n[3] Back\n>> ";
        int res;
        if (!(std::cin >> res)) { invalidInput(); continue; }

        if (res == 1) displayIndoorDepartment();
        else if (res == 2) displayOutdoorDepartment();
        else if (res == 3) break;
        else invalidInput();
    }
}

void Menu::run() {
    while (true) {
        clearTerminal();
        std::cout << "Sporting Good Inventory\n[1] View/Edit Inventory\n[2] Add New Item\n[3] Exit\n>> ";
        int res;
        if (!(std::cin >> res)) { invalidInput(); continue; }

        if (res == 1) displayItemDetailsScreen();
        else if (res == 2) displayAddItemScreen();
        else if (res == 3) {
            std::cout << "Closing system...\n";
            break;
        }
        else invalidInput();
    }
}