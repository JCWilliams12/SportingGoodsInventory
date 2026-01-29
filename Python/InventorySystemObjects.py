import os
import time

class Item:
    def __init__(self, department, section, itemName, quantity, price):
        self.department = department
        self.section = section
        self.itemName = itemName
        self.quantity = quantity
        self.price = price
        self.discount = 0.0  # Percentage as a decimal (0.1 for 10%)

    @property
    def discounted_price(self):
        return self.price * (1.0 - self.discount)

    #display item
    def __str__(self):
        return (f"{self.itemName:<15} | Qty: {self.quantity:<4} | "
                f"Price: ${self.price:>7.2f} | "
                f"Disc: {self.discount*100:>3.0f}% | "
                f"Total: ${self.discounted_price:>7.2f}")

# -=-=-= Child Classes -=-=-=-
class VolleyballItem(Item):
    def __init__(self, name, qty, price, training_type):
        super().__init__("indoor", "volleyball", name, qty, price)
        self.training_type = training_type

    def __str__(self):
        return super().__str__() + f" | Type: {self.training_type}"

class TableTennisItem(Item):
    def __init__(self, name, qty, price, style, material):
        super().__init__("indoor", "table_tennis", name, qty, price)
        self.style = style
        self.material = material

    def __str__(self):
        return super().__str__() + f" | Sty: {self.style} | Mat: {self.material}"

class CampingItem(Item):
    def __init__(self, name, qty, price, weather_rating):
        super().__init__("outdoor", "camping", name, qty, price)
        self.weather_rating = weather_rating

    def __str__(self):
        return super().__str__() + f" | Wx: {self.weather_rating}"

class SoccerItem(Item):
    def __init__(self, name, qty, price, size):
        super().__init__("outdoor", "soccer", name, qty, price)
        self.size = size

    def __str__(self):
        return super().__str__() + f" | Size: {self.size}"

class Menu:
    def __init__(self):
        #default item
        self.currentInventory = [VolleyballItem("Pro Net", 10, 50.0, "Professional")]

    #clears terminal for windows mac and linux
    def clear_terminal(self):
        os.system('cls' if os.name == 'nt' else 'clear')

    def invalid_input(self):
        print("\n!!! Invalid Input. Please try again. !!!")
        time.sleep(1)

    # -=-=-= Editing Logic -=-=-=-=-=

    # 5th tier sub menu for editing an exist item. Universal for all items
    def edit_item_screen(self, item):
        while True:
            self.clear_terminal()
            print(f"--- Editing Item: {item.itemName} ---")
            print(f"[1] Quantity: {item.quantity}")
            print(f"[2] Price:    ${item.price:.2f}")
            print(f"[3] Discount: {item.discount*100:.0f}%")
            
            # Inheritance Logic: Display specific fields based on type
            if isinstance(item, VolleyballItem):
                print(f"[5] Type:     {item.training_type}")
            elif isinstance(item, TableTennisItem):
                print(f"[5] Style:    {item.style}")
                print(f"[6] Material: {item.material}")
            elif isinstance(item, CampingItem):
                print(f"[5] Rating:   {item.weather_rating}")
            elif isinstance(item, SoccerItem):
                print(f"[5] Size:     {item.size}")

            print(f"[4] Back")
            
            choice = input("\nSelect field to edit: ")
            
            try:
                if choice == "1":
                    item.quantity = int(input(f"Enter new quantity for {item.itemName}: "))
                elif choice == "2":
                    item.price = float(input(f"Enter new price for {item.itemName}: "))
                elif choice == "3":
                    disc_input = float(input("Enter discount percentage (0-100): "))
                    item.discount = disc_input / 100.0
                elif choice == "4":
                    break
                # Inheritance Logic: Handle specific edits
                elif choice == "5":
                    if isinstance(item, VolleyballItem):
                        item.training_type = input("Enter Type (Training/Professional): ")
                    elif isinstance(item, CampingItem):
                        item.weather_rating = input("Enter Weather Rating: ")
                    elif isinstance(item, SoccerItem):
                        item.size = input("Enter Size: ")
                    elif isinstance(item, TableTennisItem):
                        item.style = input("Enter Style: ")
                    else:
                        self.invalid_input()
                elif choice == "6" and isinstance(item, TableTennisItem):
                    item.material = input("Enter Material: ")
                else:
                    self.invalid_input()
            except ValueError:
                self.invalid_input()

    # -=-=-==-=-= View & Selection Logic -=-=-=-=-=-

    # the fourth teir sub menu for viewing items, this is universal for all sub departments
    # Gemini used to create the table effect and making it look neat
    def display_filtered_items(self, dept, sect):
        while True:
            self.clear_terminal()
            print(f"--- Inventory: {dept.upper()} | {sect.upper()} ---")
            # Widened 'Final Price' column to fit extra info
            print(f"{'#':<3} {'Name':<15} | {'Qty':<4} | {'Price':<8} | {'Details'}")
            print("-" * 75)
            
            # find items in the section
            matches = [i for i in self.currentInventory if i.department == dept and i.section == sect]
            
            #if empty
            if not matches:
                print("No items found in this section.")
                input("\n[b] Back")
                break
            else:
                #display items if not empty
                for idx, item in enumerate(matches, 1):
                    print(f"[{idx}] {item}")
                
                print("\n[#] Enter item number to Edit")
                print("[b] Back")
                
                choice = input("\n>> ").lower()
                
                if choice == 'b':
                    break
                elif choice.isdigit() and 1 <= int(choice) <= len(matches):
                    self.edit_item_screen(matches[int(choice)-1])
                else:
                    self.invalid_input()

    # -=-=-=-= Add Item Screen -=-=-=--

    # second sub menu for adding an item
    def displayAddItemScreen(self):
        self.clear_terminal()
        print("--- Add New Item ---")
        try:
            name = input("Item Name: ")
            dept_choice = input("Department (1: Indoor, 2: Outdoor): ")
            dept = "indoor" if dept_choice == "1" else "outdoor"
            
            sect = ""
            new_item = None
            
            if dept == "indoor":
                sect_choice = input("Section (1: Volleyball, 2: Table Tennis): ")
                if sect_choice == "1":
                    sect = "volleyball"
                    # Capture common args
                    qty = int(input("Quantity: "))
                    price = float(input("Price: "))
                    # Capture specific args
                    t_type = input("Type (Training/Professional): ")
                    new_item = VolleyballItem(name, qty, price, t_type)
                else:
                    sect = "table_tennis"
                    qty = int(input("Quantity: "))
                    price = float(input("Price: "))
                    style = input("Style: ")
                    mat = input("Material: ")
                    new_item = TableTennisItem(name, qty, price, style, mat)
            else:
                sect_choice = input("Section (1: Camping, 2: Soccer): ")
                if sect_choice == "1":
                    sect = "camping"
                    qty = int(input("Quantity: "))
                    price = float(input("Price: "))
                    wx = input("Weather Rating: ")
                    new_item = CampingItem(name, qty, price, wx)
                else:
                    sect = "soccer"
                    qty = int(input("Quantity: "))
                    price = float(input("Price: "))
                    size = input("Size: ")
                    new_item = SoccerItem(name, qty, price, size)

            self.currentInventory.append(new_item)
            print("\nItem added successfully!")
            time.sleep(1)
        except ValueError:
            self.invalid_input()

    # -=-=-=- Navigation Logic -=-=-=-=

    # second sub menu for indoor department
    def displayIndoordepartment(self):
        while True:
            self.clear_terminal()
            res = input("Indoor Dept\n[1] Volleyball\n[2] Table Tennis\n[3] Back\n>> ")
            if res == "1":
                self.display_filtered_items("indoor", "volleyball")
            elif res == "2":
                self.display_filtered_items("indoor", "table_tennis")
            elif res == "3":
                break
            else:
                self.invalid_input()

    # 2nd sub menu for outdoor department
    def displayOutdoorDepartment(self):
        while True:
            self.clear_terminal()
            res = input("Outdoor Dept\n[1] Camping\n[2] Soccer\n[3] Back\n>> ")
            if res == "1":
                self.display_filtered_items("outdoor", "camping")
            elif res == "2":
                self.display_filtered_items("outdoor", "soccer")
            elif res == "3":
                break
            else:
                self.invalid_input()

    # first sub menu item details
    def displayItemDetailsScreen(self):
        while True:
            self.clear_terminal()
            res = input("Select Department\n[1] Indoor\n[2] Outdoor\n[3] Back\n>> ")
            if res == "1":
                self.displayIndoordepartment()
            elif res == "2":
                self.displayOutdoorDepartment()
            elif res == "3":
                break
            else:
                self.invalid_input()

    # main menu
    def run(self):
        while True:
            self.clear_terminal()
            res = input("Sporting Good Inventory\n[1] View/Edit Inventory\n[2] Add New Item\n[3] Exit\n>> ")
            if res == "1":
                self.displayItemDetailsScreen()
            elif res == "2":
                self.displayAddItemScreen()
            elif res == "3":
                print("Closing system...")
                break
            else:
                self.invalid_input()