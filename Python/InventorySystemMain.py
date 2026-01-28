#from InventorySystemOjects import *

import os
import time

def clear_terminal():
    # Check the operating system name
    if os.name == 'nt':
        # Command for Windows
        _ = os.system('cls')
    else:
        # Command for macOS and Linux (posix)
        _ = os.system('clear')

print("hello")
time.sleep(3)
clear_terminal()