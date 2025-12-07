// structures/LinkedList.cpp
#include "structures/LinkedList.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

LinkedList::~LinkedList()
{
    clear(); // فقط Nodeها رو حذف می‌کنه، چون Carها مالکیتشون منتقل شده
    // دیگه delete car نمی‌کنیم → از double delete جلوگیری شد
}

void LinkedList::pushBack(Car *car)
{
    if (!car)
        return; // ایمنی

    Node *newNode = new Node(car);
    newNode->next = nullptr;

    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

void LinkedList::pushFront(Car *car)
{
    if (!car)
        return;

    Node *newNode = new Node(car);
    newNode->next = head;
    head = newNode;
    if (!tail)
        tail = newNode; // اگر لیست خالی بود
    ++size;
}

Car *LinkedList::popFront()
{
    if (isEmpty())
        return nullptr;

    Node *tmp = head;
    Car *car = tmp->car; // مالکیت منتقل میشه
    tmp->car = nullptr;  // مهم! برای جلوگیری از delete در clear

    head = head->next;
    if (!head)
        tail = nullptr;

    delete tmp;
    --size;
    return car;
}

bool LinkedList::isEmpty() const { return head == nullptr; }
int LinkedList::getSize() const { return size; }

Car *LinkedList::getFront() const
{
    return head ? head->car : nullptr;
}

int LinkedList::findPosition(const std::string &carId) const
{
    Node *current = head;
    int pos = 1;
    while (current)
    {
        if (current->car && current->car->getId() == carId)
            return pos;
        current = current->next;
        ++pos;
    }
    return -1;
}

// ایمن شده در برابر car == nullptr
Node *LinkedList::merge(Node *left, Node *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    // ایمنی: اگر car حذف شده یا nullptr بود
    std::string leftId = left->car ? left->car->getId() : "";
    std::string rightId = right->car ? right->car->getId() : "";

    if (left->car == nullptr || (right->car != nullptr && leftId.compare(rightId) <= 0))
    {
        left->next = merge(left->next, right);
        return left;
    }
    else
    {
        right->next = merge(left, right->next);
        return right;
    }
}

void LinkedList::split(Node *source, Node *&left, Node *&right)
{
    if (!source || !source->next)
    {
        left = source;
        right = nullptr;
        return;
    }

    Node *slow = source;
    Node *fast = source->next;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    left = source;
    right = slow->next;
    slow->next = nullptr;
}

void LinkedList::mergeSortHelper(Node *&headRef)
{
    if (!headRef || !headRef->next)
        return;

    Node *left = nullptr;
    Node *right = nullptr;
    split(headRef, left, right);

    mergeSortHelper(left);
    mergeSortHelper(right);

    headRef = merge(left, right);
}

void LinkedList::mergeSort()
{
    mergeSortHelper(head);

    // بازسازی tail
    tail = head;
    if (tail)
    {
        while (tail->next)
            tail = tail->next;
    }
    // اگر لیست خالی شد، tail باید nullptr باشه → الان هست
}

void LinkedList::printList() const
{
    if (isEmpty())
    {
        std::cout << "[Empty]" << std::endl;
        return;
    }

    Node *current = head;
    std::cout << "Top -> ";
    while (current)
    {
        if (current->car)
            std::cout << current->car->getId();
        else
            std::cout << "[NULL]";

        if (current->next)
            std::cout << " -> ";
        current = current->next;
    }
    std::cout << " -> Bottom" << std::endl;
}

void LinkedList::clear()
{
    Node *cur = head;
    while (cur)
    {
        Node *next = cur->next;
        // car رو حذف نمی‌کنیم چون مالکیت منتقل شده
        // فقط اگه هنوز اشاره‌گر داره و نمی‌خوایم، می‌تونیم nullptr کنیم
        cur->car = nullptr;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    size = 0;
}