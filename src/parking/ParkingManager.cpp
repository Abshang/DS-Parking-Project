// File: parking/ParkingManager.cpp
#include "ParkingManager.h"
#include <iostream>

// constructor - O(1)
ParkingManager::ParkingManager(ParkingLot *pLot, QueueLL *pQueue)
    : lot(pLot), entryQueue(pQueue)
{
}

// O(n) - Attempts to park a car in the first available lane. n = number of stacks.
bool ParkingManager::addCar()
{
    if (entryQueue->isEmpty())
    {
        std::cout << "Entry Queue is EMPTY\n";
        return false;
    }

    Car *car = entryQueue->dequeue();

    if (!lot->parkCarInFirstAvailable(car))
    {
        std::cout << "Parking Lot is FULL. Returning car " << car->getId() << " to front of queue.\n";
        entryQueue->enqueueFront(car);
        return false;
    }

    std::cout << "Car " << car->getId() << " successfully parked in first available lane.\n";
    return true;
}

// O(1) - Attempts to park a car in a specific lane.
bool ParkingManager::addCarToStack(int stackId)
{
    if (entryQueue->isEmpty())
    {
        std::cout << "Entry Queue is EMPTY\n";
        return false;
    }

    Car *car = entryQueue->dequeue();

    if (!lot->parkCarInSpecificStack(car, stackId))
    {
        std::cout << "Cannot park in lane " << stackId << ". Returning car to front of queue.\n";
        entryQueue->enqueueFront(car);
        return false;
    }

    std::cout << "Car " << car->getId() << " parked in specified lane " << stackId << ".\n";
    return true;
}

// O(1) - Removes a car only if it is at the front of the specified stack.
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

// O(n * m) - Finds a car in the entire parking lot. n=numStacks, m=stackCapacity.
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

// O(m log m) - Sorts the contents of a specific stack. m=stackCapacity.
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

// O(n * m) - Moves all cars from stack 'i' to stack 'j' and subsequent stacks, exiting any leftovers.
// n = number of stacks, m = stack capacity.
void ParkingManager::moveStack(int fromStackId, int toStackId)
{

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
    if (source->isEmpty())
    {
        std::cout << "Stack " << fromStackId << " is already empty.\n";
        return;
    }

    LinkedList carsToMove;
    while (!source->isEmpty())
    {
        carsToMove.pushBack(source->pop());
    }
    std::cout << "All cars temporarily moved from lane " << fromStackId << ".\n";

    int targetId = toStackId;
    Node *current = carsToMove.getHead();
    while (current != nullptr && targetId <= lot->getNumStacks())
    {
        StackLL *target = lot->getStack(targetId - 1);

        while (!target->isFull() && current != nullptr)
        {
            Car *car = current->car;
            current->car = nullptr;

            target->push(car);

            std::cout << "Car " << car->getId()
                      << " moved from lane " << fromStackId
                      << " -> lane " << targetId << "\n";

            current = current->next;
        }
        targetId++;
    }

    if (current != nullptr)
    {
        std::cout << "Warning: Not enough space in subsequent lanes. "
                  << "Remaining cars must **EXIT** the parking lot to ensure lane "
                  << fromStackId << " is completely empty.\n";

        Node *toDelete = current;
        while (toDelete != nullptr)
        {
            delete toDelete->car;
            toDelete->car = nullptr;
            toDelete = toDelete->next;
        }
    }

    std::cout << "Movement completed. Lane " << fromStackId << " is now empty.\n";
}
// O(n * m) - Prints the status of the entire system (Queue + ParkingLot).
void ParkingManager::printStatus() const
{
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "                  PARKING SYSTEM STATUS                 \n";
    std::cout << "========================================================\n";
    entryQueue->print("Incoming Cars");
    std::cout << "\n";
    lot->printParkingLot();
    std::cout << "========================================================\n\n";
}