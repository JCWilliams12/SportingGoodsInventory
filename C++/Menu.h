#ifndef MENU_H
#define MENU_H

#include "Item.h"
#include <vector>

class Menu {
private:
    // Vector of pointers, polymorphism :)
    std::vector<Item*> currentInventory;

    void clearTerminal();
    void invalidInput();
    
    void pause();

public:
    Menu();
    ~Menu();
    void run();
    
    // edit/add items
    void displayAddItemScreen();
    void displayFilteredItems(std::string dept, std::string sect);
    void editItemScreen(Item* item);

    // navigation
    void displayItemDetailsScreen();
    void displayIndoorDepartment();
    void displayOutdoorDepartment();
};

#endif