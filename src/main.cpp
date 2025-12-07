#include <iostream>
#include <string>
#include "model/Car.h"
#include "structures/QueueLL.h"
#include "structures/StackLL.h"
#include "parking/ParkingLot.h"
#include "parking/ParkingManager.h"

const int NUM_STACKS = 3;
const int STACK_CAPACITY = 4;

int main()
{
    QueueLL entryQueue;

    entryQueue.enqueue(new Car("11A"));
    entryQueue.enqueue(new Car("22B"));
    entryQueue.enqueue(new Car("33C"));
    entryQueue.enqueue(new Car("44D"));
    entryQueue.enqueue(new Car("55E"));
    entryQueue.enqueue(new Car("66F"));
    entryQueue.enqueue(new Car("77G"));
    entryQueue.enqueue(new Car("100Z"));
    entryQueue.enqueue(new Car("200Y"));
    entryQueue.enqueue(new Car("300X"));

    ParkingLot parkingLot(NUM_STACKS, STACK_CAPACITY);
    ParkingManager manager(&parkingLot, &entryQueue);

    manager.printStatus();

    std::cout << "\n--- TEST: Parking in the First Available Lane (Lane 1, 2, 3) ---\n";

    manager.addCar();
    manager.addCar();

    manager.addCar();
    manager.addCar();

    manager.addCar();
    manager.addCar();

    manager.printStatus();

    std::cout << "\n--- TEST: Parking in a Specific Lane (Filling Lane 1) ---\n";
    manager.addCarToStack(1);
    manager.addCarToStack(1);

    std::cout << "\n--- TEST: Full Stack Check and Return to Queue Front ---\n";
    manager.addCarToStack(1);
    manager.addCar();

    manager.printStatus();

    std::cout << "\n--- TEST: Find Operation ---\n";
    int stackNum, position;
    manager.findCar("33C", stackNum, position);
    manager.findCar("11A", stackNum, position);
    manager.findCar("500N", stackNum, position);

    std::cout << "\n--- TEST: Remove Operation ---\n";

    manager.removeCarFromStack(1, "11A");

    manager.removeCarFromStack(1, "100Z");

    manager.removeCarFromStack(1, "22B");

    manager.printStatus();

    manager.addCarToStack(1);
    manager.addCarToStack(1);

    std::cout << "\n--- TEST: Sort Lane 1 ---\n";
    manager.sortStack(1);

    manager.printStatus();

    std::cout << "\n--- TEST: Move Lane 1 to Lane 2 (and Overflow to Lane 3) ---\n";

    manager.moveStack(1, 2);

    manager.printStatus();

    manager.addCarToStack(2);
    manager.addCarToStack(3);

    entryQueue.enqueue(new Car("A01"));
    entryQueue.enqueue(new Car("A02"));
    entryQueue.enqueue(new Car("A03"));
    entryQueue.enqueue(new Car("A04"));

    manager.addCarToStack(1);
    manager.addCarToStack(1);
    manager.addCarToStack(1);
    manager.addCarToStack(1);

    std::cout << "\n--- TEST: Move Lane 1 to Lane 3 (Insufficient Space Test) ---\n";

    manager.moveStack(1, 3);

    manager.printStatus();

    std::cout << "\n========================================================\n";
    std::cout << "TEST ENDED. Parking and Entry Queue memory automatically freed.\n";
    std::cout << "========================================================\n";

    return 0;
}