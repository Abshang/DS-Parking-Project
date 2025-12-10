// main.cpp
#include "raylib.h"
#include "gui/RaylibUtils.h"
#include "gui/InputHandler.h"
#include "model/Car.h"
#include "structures/QueueLL.h"
#include "parking/ParkingLot.h"
#include "parking/ParkingManager.h"
#include <string>
#include <vector>
#include <cstring>

// UI modes
enum UIMode
{
    UI_NORMAL,
    UI_MOVE_SELECT_SOURCE,
    UI_MOVE_SELECT_DEST,
    UI_SELECT_FOR_SORT,
    UI_SELECT_FOR_REMOVE,
    UI_PARK_SELECT_LANE
};

// helper to compute lane rectangles (must match DrawParkingModern layout)
static std::vector<Rectangle> computeLaneRects(const ParkingLot &lot)
{
    std::vector<Rectangle> rects;
    if (lot.getNumStacks() == 0)
        return rects;
    int stackMaxCapacity = lot.getStack(0)->getCapacity();
    int totalHeight = stackMaxCapacity * (CAR_HEIGHT + CAR_SPACING) + 50;
    int stackX = PARKING_START_X;
    for (int i = 0; i < lot.getNumStacks(); ++i)
    {
        Rectangle laneRect = {(float)(stackX - 10), (float)(PARKING_START_Y - 20),
                              (float)STACK_WIDTH, (float)totalHeight - 40};
        rects.push_back(laneRect);
        stackX += STACK_WIDTH + STACK_SPACING;
    }
    return rects;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Parking Lot - Final GUI");
    SetTargetFPS(60);

    // Data structures
    QueueLL entryQueue;
    ParkingLot parkingLot(5, 5); // change counts if needed
    ParkingManager manager(&parkingLot, &entryQueue);

    // Input handler
    InputHandler inputHandler;

    // UI state
    UIMode uiMode = UI_NORMAL;
    int selectedSource = -1;
    int selectedDest = -1;

    int highlightedStack = -1;
    std::string highlightedCar = "";
    float highlightTimer = 0.0f;

    Rectangle btnAddQueue = {UI_AREA_START_X, UI_AREA_START_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnParkFirst = {UI_AREA_START_X, UI_AREA_START_Y + (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnParkSelected = {UI_AREA_START_X, UI_AREA_START_Y + 2 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnRemoveQueue = {UI_AREA_START_X, UI_AREA_START_Y + 3 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnFind = {UI_AREA_START_X, UI_AREA_START_Y + 4 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnRemoveStack = {UI_AREA_START_X, UI_AREA_START_Y + 5 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnSortStack = {UI_AREA_START_X, UI_AREA_START_Y + 6 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnMoveStack = {UI_AREA_START_X, UI_AREA_START_Y + 7 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnMergeStacks = {UI_AREA_START_X, UI_AREA_START_Y + 8 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle btnAutoSort = {UI_AREA_START_X, UI_AREA_START_Y + 9 * (BUTTON_HEIGHT + SPACING), BUTTON_WIDTH, BUTTON_HEIGHT};

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // update input handler (textboxes + internal timers)
        inputHandler.update(manager, parkingLot.getNumStacks());

        // update highlight timer local copy (preferred to read from inputHandler, but use local to display)
        if (highlightTimer > 0.0f)
        {
            highlightTimer -= dt;
            if (highlightTimer <= 0.0f)
            {
                highlightedStack = -1;
                highlightedCar.clear();
                highlightTimer = 0.0f;
            }
        }

        // compute lane rects for click detection
        std::vector<Rectangle> laneRects = computeLaneRects(parkingLot);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mp = GetMousePosition();
            for (int i = 0; i < (int)laneRects.size(); ++i)
            {
                if (CheckCollisionPointRec(mp, laneRects[i]))
                {
                    int laneId = parkingLot.getStack(i)->getId(); // 1-based
                    if (uiMode == UI_MOVE_SELECT_SOURCE)
                    {
                        selectedSource = laneId;
                        uiMode = UI_MOVE_SELECT_DEST;
                        inputHandler.setOutputMessage("Source selected: Lane " + std::to_string(selectedSource) + ". Now click destination lane.");
                    }
                    else if (uiMode == UI_MOVE_SELECT_DEST)
                    {
                        selectedDest = laneId;
                        if (selectedDest == selectedSource)
                        {
                            inputHandler.setOutputMessage("Destination cannot be same as source. Select another lane.");
                        }
                        else
                        {
                            manager.moveStack(selectedSource, selectedDest);
                            highlightedStack = selectedDest;
                            highlightedCar.clear();
                            highlightTimer = 5.0f;
                            inputHandler.setOutputMessage("Moved cars from Lane " + std::to_string(selectedSource) + " to Lane " + std::to_string(selectedDest) + ".");
                            uiMode = UI_NORMAL;
                            selectedSource = selectedDest = -1;
                        }
                    }
                    else if (uiMode == UI_SELECT_FOR_SORT)
                    {
                        manager.sortStack(laneId);
                        highlightedStack = laneId;
                        highlightedCar.clear();
                        highlightTimer = 5.0f;
                        inputHandler.setOutputMessage("Sorted Lane " + std::to_string(laneId) + ".");
                        uiMode = UI_NORMAL;
                    }
                    else if (uiMode == UI_SELECT_FOR_REMOVE)
                    {
                        std::string carId = inputHandler.getCarIdBuffer();
                        if (carId.empty())
                        {
                            inputHandler.setOutputMessage("Enter Car ID before selecting lane to remove from.");
                        }
                        else
                        {
                            bool ok = manager.removeCarFromStack(laneId, carId);
                            if (ok)
                            {
                                highlightedStack = laneId;
                                highlightedCar = carId;
                                highlightTimer = 5.0f;
                                inputHandler.setOutputMessage("Car " + carId + " removed from Lane " + std::to_string(laneId) + ".");
                                // clear car id buffer
                                inputHandler.clearInput(const_cast<char *>(inputHandler.getCarIdBuffer()));
                            }
                            else
                            {
                                inputHandler.setOutputMessage("Failed to remove car (must be TOP of stack or invalid).");
                            }
                            uiMode = UI_NORMAL;
                        }
                    }
                    else if (uiMode == UI_PARK_SELECT_LANE)
                    {
                        // park specific into clicked lane
                        bool ok = manager.addCarToStack(laneId);
                        if (ok)
                        {
                            highlightedStack = laneId;
                            highlightedCar.clear();
                            highlightTimer = 5.0f;
                            inputHandler.setOutputMessage("Parked next queued car into Lane " + std::to_string(laneId) + ".");
                        }
                        else
                        {
                            inputHandler.setOutputMessage("Failed to park into Lane " + std::to_string(laneId) + ". Maybe full or queue empty.");
                        }
                        uiMode = UI_NORMAL;
                    }
                    else
                    {
                        // normal click selects lane (no immediate highlight)
                        selectedSource = laneId;
                        inputHandler.setOutputMessage("Selected Lane " + std::to_string(laneId) + ".");
                    }
                    break;
                }
            }
        }

        if (DrawModernButton(btnAddQueue, "Add Car to Queue", ACCENT_BLUE))
        {
            inputHandler.handleAddCarToQueue(entryQueue);
        }

        if (DrawModernButton(btnParkFirst, "Park (First Available)", ACCENT_GREEN))
        {
            inputHandler.handleParkFirst(manager);
        }

        if (DrawModernButton(btnParkSelected, "Park in Selected Lane (click lane)", ACCENT_BLUE))
        {
            uiMode = UI_PARK_SELECT_LANE;
            inputHandler.setOutputMessage("Park: Click a lane to place the next car from queue.");
        }

        if (DrawModernButton(btnRemoveQueue, "Remove Car from Queue", ACCENT_RED))
        {
            if (!entryQueue.isEmpty())
            {
                Car *c = entryQueue.dequeue();
                inputHandler.setOutputMessage("Removed from queue: " + c->getId());
                delete c;
            }
            else
            {
                inputHandler.setOutputMessage("Queue empty.");
            }
        }

        if (DrawModernButton(btnFind, "Find Car (by ID)", ACCENT_ORANGE))
        {
            inputHandler.handleFindCar(manager);
            std::string hid = inputHandler.getHighlightCarId();
            if (!hid.empty())
            {
                highlightedCar = hid;
                highlightTimer = 5.0f;
            }
        }

        if (DrawModernButton(btnRemoveStack, "Remove Car from Lane (click lane)", ACCENT_PURPLE))
        {
            uiMode = UI_SELECT_FOR_REMOVE;
            inputHandler.setOutputMessage("Remove: Enter Car ID then click lane to remove (only TOP allowed).");
        }

        if (DrawModernButton(btnSortStack, "Sort Lane (click lane)", ACCENT_GREEN))
        {
            uiMode = UI_SELECT_FOR_SORT;
            inputHandler.setOutputMessage("Select lane to sort (merge sort).");
        }

        if (DrawModernButton(btnMoveStack, "Move Stack (select source -> dest)", ACCENT_BLUE))
        {
            uiMode = UI_MOVE_SELECT_SOURCE;
            inputHandler.setOutputMessage("Move: Click source lane.");
        }

        if (DrawModernButton(btnMergeStacks, "Merge Stack (src -> dst)", ACCENT_ORANGE))
        {
            uiMode = UI_MOVE_SELECT_SOURCE;
            inputHandler.setOutputMessage("Merge: Click source lane (then destination).");
        }

        if (DrawModernButton(btnAutoSort, "Auto-Sort All Lanes", ACCENT_GREEN))
        {
            for (int i = 1; i <= parkingLot.getNumStacks(); ++i)
                manager.sortStack(i);
            inputHandler.setOutputMessage("All lanes sorted.");
        }

        // draw
        BeginDrawing();
        ClearBackground(BG_PRIMARY);

        DrawTitle("Parking Lot Simulator - Final", UI_AREA_START_X, 8);

        // draw queue and parking (highlight from inputHandler state)
        DrawQueueModern(entryQueue);
        // if InputHandler has a highlight car, prefer it
        std::string handlerH = inputHandler.getHighlightCarId();
        if (!handlerH.empty())
        {
            DrawParkingModern(parkingLot, -1, handlerH);
        }
        else
        {
            DrawParkingModern(parkingLot, highlightedStack, highlightedCar);
        }

        // draw textboxes (car id at top)
        DrawModernTextBox(Rectangle{UI_AREA_START_X, UI_AREA_START_Y - 40, BUTTON_WIDTH, 40},
                          inputHandler.getCarIdBuffer(), inputHandler.isCarIdEditMode(), "Car ID");

        // draw buttons visually again for hover state
        DrawModernButton(btnAddQueue, "Add Car to Queue", ACCENT_BLUE);
        DrawModernButton(btnParkFirst, "Park (First Available)", ACCENT_GREEN);
        DrawModernButton(btnParkSelected, "Park in Selected Lane (click lane)", ACCENT_BLUE);
        DrawModernButton(btnRemoveQueue, "Remove Car from Queue", ACCENT_RED);
        DrawModernButton(btnFind, "Find Car (by ID)", ACCENT_ORANGE);
        DrawModernButton(btnRemoveStack, "Remove Car from Lane (click lane)", ACCENT_PURPLE);
        DrawModernButton(btnSortStack, "Sort Lane (click lane)", ACCENT_GREEN);
        DrawModernButton(btnMoveStack, "Move Stack (select src -> dest)", ACCENT_BLUE);
        DrawModernButton(btnMergeStacks, "Merge Stack (src -> dst)", ACCENT_ORANGE);
        DrawModernButton(btnAutoSort, "Auto-Sort All Lanes", ACCENT_GREEN);

        // selected lane indicator
        if (selectedSource >= 1)
        {
            DrawText(("Selected Lane: " + std::to_string(selectedSource)).c_str(),
                     UI_AREA_START_X, UI_AREA_START_Y + 11 * (BUTTON_HEIGHT + SPACING) + 8, 14, TEXT_PRIMARY);
        }

        // output panel uses InputHandler message
        DrawOutputPanel(inputHandler.getOutputMessage(), UI_AREA_START_X, UI_AREA_START_Y + 12 * (BUTTON_HEIGHT + SPACING) + 24, BUTTON_WIDTH);

        EndDrawing();
    }

    // cleanup
    CloseWindow();
    return 0;
}
