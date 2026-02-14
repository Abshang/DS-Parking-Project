// main.cpp
#include "parking/ParkingManager.h"
#include "structures/QueueLL.h"
#include <iostream>
#include <string>

using namespace std;

void displayMenu()
{
    cout << "\n╔════════════════════════════════════════════════════╗\n";
    cout << "║         PARKING MANAGEMENT SYSTEM MENU            ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
    cout << "  1.  Add Car to Entry Queue\n";
    cout << "  2.  Park Car in First Available Lane\n";
    cout << "  3.  Park Car in Specific Lane\n";
    cout << "  4.  Find Car in Parking Lot\n";
    cout << "  5.  Remove Car from Lane (Top Only)\n";
    cout << "  6.  Sort a Lane (Merge Sort)\n";
    cout << "  7.  Move Stack (From Lane to Lane)\n";
    cout << "  8.  Display System Status\n";
    cout << "  9.  Display Entry Queue\n";
    cout << "  0.  Exit\n";
    cout << "════════════════════════════════════════════════════\n";
    cout << "Enter your choice: ";
}

int main()
{
    int numLanes, capacity;

    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║    Welcome to Parking Management System!         ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n\n";

    cout << "Enter number of parking lanes: ";
    cin >> numLanes;
    cout << "Enter capacity per lane: ";
    cin >> capacity;

    ParkingLot lot(numLanes, capacity);
    QueueLL queue;
    ParkingManager manager(&lot, &queue);

    int choice;
    string carId;
    int laneNum, fromLane, toLane;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        switch (choice)
        {
        case 1:
        {
            cout << "\n→ Enter Car ID: ";
            getline(cin, carId);
            if (carId.empty())
            {
                cout << "ERROR: Car ID cannot be empty!\n";
                break;
            }
            Car *car = new Car(carId);
            queue.enqueue(car);
            cout << "✓ Car " << carId << " added to entry queue.\n";
            break;
        }

        case 2:
        {
            if (queue.isEmpty())
            {
                cout << "ERROR: Entry queue is empty!\n";
                break;
            }
            manager.addCar();
            break;
        }

        case 3:
        {
            if (queue.isEmpty())
            {
                cout << "ERROR: Entry queue is empty!\n";
                break;
            }
            cout << "\n→ Enter Lane Number (1-" << numLanes << "): ";
            cin >> laneNum;
            manager.addCarToStack(laneNum);
            break;
        }

        case 4:
        {
            cout << "\n→ Enter Car ID to find: ";
            getline(cin, carId);
            int stackNum, position;
            manager.findCar(carId, stackNum, position);
            break;
        }

        case 5:
        {
            cout << "\n→ Enter Lane Number: ";
            cin >> laneNum;
            cin.ignore();
            cout << "→ Enter Car ID to remove: ";
            getline(cin, carId);
            manager.removeCarFromStack(laneNum, carId);
            break;
        }

        case 6:
        {
            cout << "\n→ Enter Lane Number to sort: ";
            cin >> laneNum;
            manager.sortStack(laneNum);
            break;
        }

        case 7:
        {
            cout << "\n→ Enter source lane (FROM): ";
            cin >> fromLane;
            cout << "→ Enter destination lane (TO): ";
            cin >> toLane;
            manager.moveStack(fromLane, toLane);
            break;
        }

        case 8:
        {
            manager.printStatus();
            break;
        }

        case 9:
        {
            queue.print("Current Queue");
            break;
        }

        case 0:
        {
            cout << "\n✓ Thank you for using Parking Management System!\n";
            cout << "Exiting...\n\n";
            break;
        }

        default:
            cout << "\n✗ Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

    // Cleanup
    queue.clear();

    return 0;
}