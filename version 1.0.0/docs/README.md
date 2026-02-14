Parking Lot Management System

A C++ project implementing a complete parking simulation using custom data structures and a simple Raylib-based GUI.

Overview

This project models a parking lot where entering cars are stored in a queue and then assigned to one of several parking rows, each represented as a stack. All the core structures (LinkedList, Stack, Queue) are written manually without using STL containers. A graphical interface is also included to visualize the parking process and allow user interaction.

Features

Queue-based entrance system

Stack-based parking rows

Find and locate cars inside the lot

Remove cars (only from the top of a stack)

Merge sort implemented for sorting a selected stack

Move cars between stacks with automatic overflow handling

Raylib GUI for displaying stacks, queues, and controls

Project Structure
Parking_project/
│
├── models/ # Car and Node classes
├── structures/ # LinkedList, StackLL, QueueLL
├── parking/ # ParkingLot and ParkingManager logic
├── gui/ # Rendering and input handling
└── main.cpp # Program entry

Authors :

Fatemeh Abshang
