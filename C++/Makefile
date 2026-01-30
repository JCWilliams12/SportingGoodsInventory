# Compiler variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Target executable name
TARGET = inventory_system

# Source files
SRCS = InventorySystemMain.cpp Item.cpp Menu.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default build
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJS)