// model/Node.cpp
#include "Node.h"

Node::Node(Car *c, Node *n) : car(c), next(n) {}
Node::~Node() = default;