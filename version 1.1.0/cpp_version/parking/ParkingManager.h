// parking/ParkingManager.h

#pragma once

#include "ParkingLot.h"

#include "structures/QueueLL.h"

#include <unordered_set>

class ParkingManager

{

private:
    ParkingLot *lot;

    QueueLL *entryQueue;

    std::unordered_set<std::string> licensePlates;

public:

    ParkingManager(ParkingLot *pLot, QueueLL *pQueue); // O(1)

    ~ParkingManager() = default; // O(1)

    bool addCar(); // O(n)
    bool addCarToQueue(Car *car); // O(1)

    bool addCarToQueue(Car *car); // O(1)

    bool addCarToStack(int stackId); // O(1)

    bool removeCarFromStack(int stackId, const std::string &carId); // O(1)

    bool findCar(const std::string &carId, int &stackNum, int &position); // O(n * m)

    void sortStack(int stackId); // O(m log m)

    void moveStack(int fromStackId, int toStackId); // O(n * m)

    void printStatus() const; // O(n * m)
};
