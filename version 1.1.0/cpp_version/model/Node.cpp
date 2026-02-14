#include "Node.h"

Node::Node(Car *c, Node *n) : car(c), next(n) {} // O(1)