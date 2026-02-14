# Parking Management System

A comprehensive parking lot management system built with C++ and Raylib, implementing fundamental data structures including linked lists, stacks, and queues.

## 📋 Project Overview

This project simulates real-world parking lot operations using custom-implemented data structures. The system manages vehicle arrivals through a queue and organizes parking spaces using multiple independent stacks, each implemented with linked lists.

**Developed by:** Fatemeh Abshang & Amir Gerivani  
**Course:** Data Structures - Midterm Project

## ✨ Key Features

- **Queue-based Entry System**: Vehicles arrive and wait in a FIFO queue
- **Stack-based Parking Lanes**: Each parking row operates as a LIFO stack
- **Smart Parking Operations**:
  - Park cars in the first available stack or user-selected stack
  - Search for specific vehicles across all parking lanes
  - Remove cars from stack tops only (realistic constraint)
- **Advanced Algorithms**:
  - Recursive merge sort for organizing individual stacks
  - Car transfer between stacks with automatic overflow handling
- **Interactive GUI**: Real-time visualization using Raylib framework
- **Manual Implementation**: All data structures built from scratch without STL

## 🏗️ System Architecture

### Core Operations

1. **Enqueue Cars**: Add arriving vehicles to the entrance queue
2. **Park Vehicle**: Move cars from queue to parking stacks
3. **Search Vehicle**: Locate specific cars within the parking lot
4. **Remove Vehicle**: Exit cars from stack tops only
5. **Sort Stack**: Apply recursive merge sort to individual lanes
6. **Transfer Cars**: Move vehicles between stacks with capacity management

### Project Structure

```
Parking_project/
├── src/
│   ├── main.cpp                 # Application entry point
│   ├── model/                   # Core data models
│   │   ├── Car.h / Car.cpp      # Vehicle representation
│   │   └── Node.h / Node.cpp    # Linked list node
│   ├── structures/              # Data structure implementations
│   │   ├── LinkedList.h / LinkedList.cpp
│   │   ├── StackLL.h / StackLL.cpp
│   │   └── QueueLL.h / QueueLL.cpp
│   ├── parking/                 # Business logic
│   │   ├── ParkingLot.h / ParkingLot.cpp
│   │   └── ParkingManager.h / ParkingManager.cpp
│   └── gui/                     # Graphical interface
│       ├── RaylibUtils.h / RaylibUtils.cpp
│       └── InputHandler.h / InputHandler.cpp
├── raylib/                      # Raylib framework
├── bin/                         # Compiled executable
├── build.bat                    # Build script
├── CMakeLists.txt              # CMake configuration
└── README.md
```

## 🔧 Component Details

### Model Layer

**Car Class**

- Represents individual vehicles with unique identifiers
- Lightweight design for efficient storage
- Supports comparison and search operations

**Node Class**

- Building block for all linked structures
- Contains car data and next-node pointer
- Enables dynamic memory allocation

### Data Structures Layer

**LinkedList**

- Foundation for stacks and queues
- Dynamic node-based implementation
- Supports insertion, deletion, and traversal

**StackLL (Stack with Linked List)**

- LIFO structure modeling parking lanes
- Operations: push, pop, peek, isEmpty, isFull
- Enforces realistic parking constraints

**QueueLL (Queue with Linked List)**

- FIFO structure for entrance management
- Operations: enqueue, dequeue, front
- Maintains arrival order fairness

### Business Logic Layer

**ParkingLot**

- Manages multiple parking stacks
- Implements core parking operations
- Handles vehicle search and sorting
- Coordinates stack-to-stack transfers

**ParkingManager**

- High-level system controller
- Bridges GUI and parking logic
- Validates user input and operations
- Maintains system consistency

### GUI Layer

**RaylibUtils**

- Renders parking lot visualization
- Draws stacks, queues, and vehicles
- Provides interactive UI components
- Updates display in real-time

**InputHandler**

- Processes mouse and keyboard events
- Routes user actions to business logic
- Provides feedback for invalid operations
- Maintains clean separation of concerns

## 🚀 Getting Started

### Prerequisites

- C++ compiler with C++11 support (MinGW-w64 recommended)
- CMake 3.10 or higher
- Raylib 5.0 (included in project)

### Building the Project

**Windows (MinGW):**

```bash
./build.bat
```

**Using CMake:**

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running the Application

```bash
cd bin
./ParkingLot.exe
```

## 🎮 How to Use

1. **Add Cars to Queue**: Click to enqueue arriving vehicles
2. **Park Vehicles**:
   - Auto-park to first available stack
   - Or select specific stack for parking
3. **Search for Car**: Enter car ID to locate vehicle
4. **Remove Car**: Click stack top to remove vehicles
5. **Sort Stack**: Apply merge sort to organize lanes
6. **Transfer Cars**: Move vehicles between stacks

## 🧮 Technical Highlights

### Algorithms & Complexity

- **Parking Operations**: O(1) for stack push/pop
- **Vehicle Search**: O(n×m) where n=stacks, m=avg stack size
- **Stack Sorting**: O(n log n) using recursive merge sort
- **Queue Operations**: O(1) for enqueue/dequeue

### Design Patterns

- **Modular Architecture**: Clear separation of concerns
- **Encapsulation**: Private data with public interfaces
- **Abstraction**: High-level operations hide implementation details

### Memory Management

- Dynamic allocation using raw pointers
- Manual memory cleanup to prevent leaks
- No dependency on STL containers

## 📚 Learning Outcomes

This project demonstrates proficiency in:

- ✅ Manual implementation of fundamental data structures
- ✅ Pointer manipulation and dynamic memory management
- ✅ Recursive algorithm design (merge sort)
- ✅ Time complexity analysis and optimization
- ✅ Object-oriented programming in C++
- ✅ GUI development with Raylib
- ✅ Software architecture and modular design
- ✅ Version control with Git

## 🙏 Acknowledgments

- Course instructors for project requirements and guidance
- Raylib community for the excellent graphics framework
- Data Structures course materials and resources
