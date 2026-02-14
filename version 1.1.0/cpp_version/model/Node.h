#pragma once

#include "Car.h"

class Node

{

public:
    Car *car;

    Node *next;

    explicit Node(Car *c = nullptr, Node *n = nullptr); // O(1)

    ~Node() = default; // O(1)

    Node(const Node &) = delete;

    Node &operator=(const Node &) = delete;
};