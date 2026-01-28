from typing import Literal

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

    def run(self):
        while 1:
            userResponse = input("Sporting Good Inventory\n" \
            "\n" \
            "[1] Item Details\n" \
            "[2] Add Item\n")

            if(userResponse == 1):
                1
            elif(userResponse == 2):
                1
            else:
                

