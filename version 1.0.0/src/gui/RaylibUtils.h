#pragma once
#include "raylib.h"
#include <string>
#include "model/Car.h"
#include "structures/QueueLL.h"
#include "parking/ParkingLot.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800

#define CAR_WIDTH 90
#define CAR_HEIGHT 50

#define STACK_WIDTH 130
#define STACK_SPACING 25
#define CAR_SPACING 8

#define PARKING_START_X 50
#define PARKING_START_Y 200

#define QUEUE_ITEM_WIDTH 100
#define QUEUE_START_X 50
#define QUEUE_START_Y 50

#define UI_AREA_START_X 950
#define UI_AREA_START_Y 50
#define BUTTON_HEIGHT 45
#define BUTTON_WIDTH 400
#define SPACING 12

#define TITLE_FONT_SIZE 28
#define TEXT_FONT_SIZE 18

// background
const Color BG_PRIMARY = {25, 28, 34, 255};   // very soft dark blue-gray
const Color BG_SECONDARY = {38, 41, 48, 255}; // slightly lighter soft gray
const Color BG_TERTIARY = {52, 55, 63, 255};  // medium gray for panels

// accent colors
const Color ACCENT_BLUE = {120, 160, 230, 255};   // soft pastel blue
const Color ACCENT_GREEN = {125, 210, 165, 255};  // soft mint green
const Color ACCENT_YELLOW = {235, 220, 130, 255}; // soft vanilla yellow
const Color ACCENT_RED = {220, 125, 125, 255};    // soft rose red
const Color ACCENT_PURPLE = {165, 135, 225, 255}; // soft lavender
const Color ACCENT_ORANGE = {230, 170, 120, 255}; // soft peach orange

// text colors
const Color TEXT_PRIMARY = {240, 240, 250, 255};   // almost white
const Color TEXT_SECONDARY = {165, 170, 185, 255}; // soft muted gray-blue

const Color SURFACE = {70, 75, 85, 255}; // soft slate gray

// cars
void DrawCarModern(const Car *car, int x, int y, Color color, bool highlight = false);

// queue Visualization
void DrawQueueModern(const QueueLL &queue);

// parking Lot Visualization
void DrawParkingModern(const ParkingLot &lot, int highlightedStackId,
                       const std::string &highlightedCarId);

// buttons
bool DrawModernButton(Rectangle rect, const char *text, Color color, bool disabled = false);

// text Boxes
void DrawModernTextBox(Rectangle rect, const char *text, bool editMode, const char *label);
void UpdateModernTextBox(Rectangle rect, char *text, bool &editMode, int maxChars);

// output Message Panel
void DrawOutputPanel(const std::string &message, int x, int y, int width);

// section Titles
void DrawTitle(const char *text, int x, int y);
void DrawSectionDivider(int y);
