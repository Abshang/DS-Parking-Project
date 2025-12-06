// File: Node.h
// Description: Defines Node for LinkedList. Contains pointer to Car and next Node.

#pragma once
#include "Car.h"

class Node
{
public:
    Car *car;
    Node *next;
    Node(Car *c);
};
