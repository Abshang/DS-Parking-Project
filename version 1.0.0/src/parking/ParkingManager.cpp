// parking/ParkingManager.cpp
#include "ParkingManager.h"
#include <iostream>

// constructor - O(1)
ParkingManager::ParkingManager(ParkingLot *pLot, QueueLL *pQueue)
    : lot(pLot), entryQueue(pQueue)
{
}

// O(n) - attempts to park a car in the first available lane. n = number of stacks.
bool ParkingManager::addCar()
{
    if (!entryQueue || entryQueue->isEmpty())
    {
        std::cout << "Entry Queue is EMPTY\n";
        return false;
    }

    Car *car = entryQueue->dequeue();
    if (!car)
    {
        std::cout << "Dequeue returned nullptr\n";
        return false;
    }

    // all line is full 
    if (!lot->parkCarInFirstAvailable(car))
    {
        std::cout << "Parking Lot is FULL. Returning car " << car->getId() << " to front of queue.\n";
        entryQueue->enqueueFront(car);
        return false;
    }

    std::cout << "Car " << car->getId() << " successfully parked in first available lane.\n";
    return true;
}

// O(1) - attempts to park a car in a specific lane.
bool ParkingManager::addCarToStack(int stackId)
{
    if (!entryQueue || entryQueue->isEmpty())
    {
        std::cout << "Entry Queue is EMPTY\n";
        return false;
    }

    Car *car = entryQueue->dequeue();
    if (!car)
    {
        std::cout << "Dequeue returned nullptr\n";
        return false;
    }

    if (!lot->parkCarInSpecificStack(car, stackId))
    {
        std::cout << "Cannot park in lane " << stackId << ". Returning car to front of queue.\n";
        entryQueue->enqueueFront(car);
        return false;
    }

    std::cout << "Car " << car->getId() << " parked in specified lane " << stackId << ".\n";
    return true;
}

// O(1) - removes a car only if it is at the front of the specified stack.
bool ParkingManager::removeCarFromStack(int stackId, const std::string &carId)
{
    if (!lot->removeCarFromStack(stackId, carId))
    {
        std::cout << "Cannot remove car " << carId << " from lane " << stackId << " (not at front or invalid lane)\n";
        return false;
    }
    std::cout << "Car " << carId << " successfully exited from lane " << stackId << ".\n";
    return true;
}

// O(n * m) - finds a car in the entire parking lot. n=numStacks, m=stackCapacity.
bool ParkingManager::findCar(const std::string &carId, int &stackNum, int &position)
{
    if (!lot->findCar(carId, stackNum, position))
    {
        std::cout << "Car " << carId << " NOT FOUND in parking lot.\n";
        return false;
    }
    std::cout << "Car " << carId << " found in Lane " << stackNum
              << " at position " << position << " (1 = top)\n";
    return true;
}

// O(m log m) - sorts the contents of a specific stack. m=stackCapacity.
void ParkingManager::sortStack(int stackId)
{
    if (stackId < 1 || stackId > lot->getNumStacks())
    {
        std::cout << "Invalid stack number: " << stackId << "\n";
        return;
    }
    lot->sortStack(stackId);
    std::cout << "Lane " << stackId << " sorted successfully using Merge Sort.\n";
}

// O(n * m) - moves all cars from stack 'fromStackId' to stack 'toStackId' and subsequent stacks.
// If not enough space, remaining cars are removed (deleted) so that the source stack becomes empty.
void ParkingManager::moveStack(int fromStackId, int toStackId)
{
    // Validate indices
    if (!lot)
    {
        std::cout << "ParkingLot pointer is null\n";
        return;
    }

    if (fromStackId < 1 || fromStackId > lot->getNumStacks() ||
        toStackId < 1 || toStackId > lot->getNumStacks())
    {
        std::cout << "Invalid stack number(s)\n";
        return;
    }
    if (fromStackId == toStackId)
    {
        std::cout << "Cannot move stack to itself!\n";
        return;
    }

    StackLL *source = lot->getStack(fromStackId - 1);
    if (!source)
    {
        std::cout << "Source stack is null\n";
        return;
    }
    if (source->isEmpty())
    {
        std::cout << "Stack " << fromStackId << " is already empty.\n";
        return;
    }

    LinkedList carsToMove;
    while (!source->isEmpty())
    {
        Car *c = source->pop();
        if (c)
            carsToMove.pushFront(c);
    }
    std::cout << "All cars temporarily moved from lane " << fromStackId << ".\n";

    int currentIndex = toStackId - 1;
    Node *node = carsToMove.getHead();

    while (node && currentIndex < lot->getNumStacks())
    {
        StackLL *target = lot->getStack(currentIndex);
        // fill target as much as possible
        while (node && !target->isFull())
        {
            Car *car = node->car;
            // try to push into target
            bool pushed = target->push(car);
            if (!pushed)
            {
                break;
            }
            node->car = nullptr;

            std::cout << "Car " << car->getId() << " moved from lane "
                      << fromStackId << " -> lane " << (currentIndex + 1) << "\n";

            node = node->next;
        }
        currentIndex++;
    }

    Node *rem = node;
    while (rem)
    {
        if (rem->car)
        {
            std::cout << "Car " << rem->car->getId() << " cannot be moved (no space). Exiting and freeing memory.\n";
            delete rem->car;
            rem->car = nullptr;
        }
        rem = rem->next;
    }

    carsToMove.clear();

    std::cout << "Movement completed. Lane " << fromStackId << " is now empty.\n";
}

// O(n * m) - Prints the status of the entire system (Queue + ParkingLot).
void ParkingManager::printStatus() const
{
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "                  PARKING SYSTEM STATUS                 \n";
    std::cout << "========================================================\n";
    if (entryQueue)
        entryQueue->print("Incoming Cars");
    std::cout << "\n";
    if (lot)
        lot->printParkingLot();
    std::cout << "========================================================\n\n";
}
