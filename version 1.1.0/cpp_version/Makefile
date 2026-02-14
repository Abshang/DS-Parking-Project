# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories
MODEL_DIR = model
STRUCT_DIR = structures
PARKING_DIR = parking

# Object files
OBJS = main.o \
       $(MODEL_DIR)/Car.o \
       $(MODEL_DIR)/Node.o \
       $(STRUCT_DIR)/LinkedList.o \
       $(STRUCT_DIR)/QueueLL.o \
       $(STRUCT_DIR)/StackLL.o \
       $(PARKING_DIR)/ParkingLot.o \
       $(PARKING_DIR)/ParkingManager.o

# Target executable
TARGET = parking_system

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile main.cpp
main.o: main.cpp $(PARKING_DIR)/ParkingManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Model files
$(MODEL_DIR)/Car.o: $(MODEL_DIR)/Car.cpp $(MODEL_DIR)/Car.h
	$(CXX) $(CXXFLAGS) -c $(MODEL_DIR)/Car.cpp -o $(MODEL_DIR)/Car.o

$(MODEL_DIR)/Node.o: $(MODEL_DIR)/Node.cpp $(MODEL_DIR)/Node.h $(MODEL_DIR)/Car.h
	$(CXX) $(CXXFLAGS) -c $(MODEL_DIR)/Node.cpp -o $(MODEL_DIR)/Node.o

# Structure files
$(STRUCT_DIR)/LinkedList.o: $(STRUCT_DIR)/LinkedList.cpp $(STRUCT_DIR)/LinkedList.h $(MODEL_DIR)/Node.h
	$(CXX) $(CXXFLAGS) -c $(STRUCT_DIR)/LinkedList.cpp -o $(STRUCT_DIR)/LinkedList.o

$(STRUCT_DIR)/QueueLL.o: $(STRUCT_DIR)/QueueLL.cpp $(STRUCT_DIR)/QueueLL.h $(STRUCT_DIR)/LinkedList.h
	$(CXX) $(CXXFLAGS) -c $(STRUCT_DIR)/QueueLL.cpp -o $(STRUCT_DIR)/QueueLL.o

$(STRUCT_DIR)/StackLL.o: $(STRUCT_DIR)/StackLL.cpp $(STRUCT_DIR)/StackLL.h $(STRUCT_DIR)/LinkedList.h
	$(CXX) $(CXXFLAGS) -c $(STRUCT_DIR)/StackLL.cpp -o $(STRUCT_DIR)/StackLL.o

# Parking files
$(PARKING_DIR)/ParkingLot.o: $(PARKING_DIR)/ParkingLot.cpp $(PARKING_DIR)/ParkingLot.h $(STRUCT_DIR)/StackLL.h
	$(CXX) $(CXXFLAGS) -c $(PARKING_DIR)/ParkingLot.cpp -o $(PARKING_DIR)/ParkingLot.o

$(PARKING_DIR)/ParkingManager.o: $(PARKING_DIR)/ParkingManager.cpp $(PARKING_DIR)/ParkingManager.h $(PARKING_DIR)/ParkingLot.h
	$(CXX) $(CXXFLAGS) -c $(PARKING_DIR)/ParkingManager.cpp -o $(PARKING_DIR)/ParkingManager.o

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned all build files"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean run rebuild