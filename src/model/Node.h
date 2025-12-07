// src/model/Node.h
#pragma once
#include "Car.h"

class Node
{
public:
    Car *car;
    Node *next;

    explicit Node(Car *c = nullptr, Node *n = nullptr)
        : car(c), next(n) {}

    ~Node() = default;

    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;
};