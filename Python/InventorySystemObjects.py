from typing import Literal

import os
import time

class Item:
    department = ""
    section = ""
    itemName = ""
    quantity = 0
    price = 0
    discount = 0.0

    #constructor
    def __init__(
            self, 
            department: Literal["indoor", "outdoor"],
            section: Literal["volleyball", "table_tennis", "camping", "soccer"],
            itemName,
            quantity,
            price
            ):
        
        self.department = department
        self.section = section
        self.itemName = itemName
        self.quantity = quantity
        self.price = price


    def discountedPrice(self):
        return self.price * self.discount


class Menu:
    currentInventory = []

    #Clears the terminal
    def clear_terminal(self):
        # Check the operating system name
        if os.name == 'nt':
            # Command for Windows
            _ = os.system('cls')
        else:
            # Command for macOS and Linux (posix)
            _ = os.system('clear')
    
    #Warns the user they made an incorrect input
    def invalid_input(self):
        print("Please Enter A Valid Input")
        time.sleep(1)
        
    #Displays the item details menu    
    def displayItemDetailsScreen(self):
        return

    #Displays the add item menu    
    def displayAddItemScreen(self):
        return

    #displays The main menu
    def run(self):
        while 1:
            self.clear_terminal()
            userResponse = input("Sporting Good Inventory\n" \
                "\n" \
                "[1] Item Details\n" \
                "[2] Add Item\n")

            if(userResponse == "1"):
                self.clear_terminal()
                self.displayItemDetailsScreen()
            elif(userResponse == "2"):
                self.clear_terminal()
                self.displayAddItemScreen()
            else:
                self.clear_terminal()
                self.invalid_input()
                

