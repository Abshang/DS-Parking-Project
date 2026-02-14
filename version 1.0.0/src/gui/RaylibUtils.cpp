// RaylibUtils.cpp
#include "RaylibUtils.h"
#include <cstring>
#include <cmath>
#include <vector>

// small helpers
static int clampInt(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }
static Color fade(Color c, float factor)
{
    Color r = c;
    r.r = (unsigned char)clampInt((int)(c.r * factor), 0, 255);
    r.g = (unsigned char)clampInt((int)(c.g * factor), 0, 255);
    r.b = (unsigned char)clampInt((int)(c.b * factor), 0, 255);
    return r;
}

// draw a soft-styled car `highlight` draws a gentle glow.
void DrawCarModern(const Car *car, int x, int y, Color color, bool highlight)
{
    if (!car)
        return;

    // soft shadow
    Rectangle shadow = {(float)x + 4, (float)y + 6, (float)CAR_WIDTH, (float)CAR_HEIGHT};
    DrawRectangleRounded(shadow, 0.18f, 8, (Color){0, 0, 0, 48});

    // body
    Rectangle body = {(float)x, (float)y, (float)CAR_WIDTH, (float)CAR_HEIGHT};
    DrawRectangleRounded(body, 0.18f, 8, color);

    // subtle shine (smaller offset than before)
    Rectangle shine = {(float)x + 6, (float)y + 6, CAR_WIDTH - 12, CAR_HEIGHT / 3.2f};
    Color shineColor = fade(color, 1.08f);
    shineColor.a = 90;
    DrawRectangleRounded(shine, 0.18f, 8, shineColor);

    // window
    Rectangle window = {(float)x + 12, (float)y + 9, CAR_WIDTH - 24, CAR_HEIGHT - 18};
    DrawRectangleRounded(window, 0.14f, 6, (Color){210, 225, 235, 220});

    // soft border
    DrawRectangleRoundedLines(body, 0.18f, 8, 1, SURFACE);

    // gentle highlight glow
    if (highlight)
    {
        // three rings with decreasing alpha
        for (int i = 0; i < 3; ++i)
        {
            float inset = i * 3.0f;
            Rectangle glow = {body.x - inset, body.y - inset, body.width + inset * 2.0f, body.height + inset * 2.0f};
            unsigned char a = (unsigned char)clampInt(110 - i * 36, 20, 110);
            Color glc = fade(ACCENT_YELLOW, 0.9f);
            glc.a = a;
            DrawRectangleRoundedLines(glow, 0.18f, 8, 2 - i, glc);
        }
    }

    // car ID text (centered) - shadow + foreground
    std::string id = car->getId();
    int fontSize = 14;
    int textWidth = MeasureText(id.c_str(), fontSize);
    int textX = x + (CAR_WIDTH - textWidth) / 2;
    int textY = y + (CAR_HEIGHT - fontSize) / 2;
    DrawText(id.c_str(), textX + 1, textY + 1, fontSize, (Color){0, 0, 0, 110});
    DrawText(id.c_str(), textX, textY, fontSize, TEXT_PRIMARY);
}

// draws up to 7 items and a "+N more" if queue is larger.
void DrawQueueModern(const QueueLL &queue)
{
    Rectangle panel = {QUEUE_START_X - 12, QUEUE_START_Y - 12, QUEUE_ITEM_WIDTH * 7 + 120, 128};
    DrawRectangleRounded(panel, 0.08f, 8, BG_SECONDARY);
    DrawRectangleRoundedLines(panel, 0.08f, 8, 1, BG_TERTIARY);

    DrawText("ENTRY QUEUE (FIFO)", QUEUE_START_X + 6, QUEUE_START_Y - 6, 20, TEXT_PRIMARY);

    std::string status = std::to_string(queue.getSize()) + " cars";
    Rectangle badge = {QUEUE_START_X + 260, QUEUE_START_Y + 2, 88, 24};
    DrawRectangleRounded(badge, 0.35f, 6, ACCENT_BLUE);
    int statusWidth = MeasureText(status.c_str(), 14);
    DrawText(status.c_str(), badge.x + (badge.width - statusWidth) / 2, badge.y + 4, 14, TEXT_PRIMARY);

    int x = QUEUE_START_X;
    int y = QUEUE_START_Y + 42;
    Node *current = queue.getHead();
    int count = 0;

    while (current && count < 7)
    {
        DrawCarModern(current->car, x, y, ACCENT_ORANGE, false);

        if (current->next && count < 6)
        {
            // small arrow
            int arrowX = x + CAR_WIDTH + 8;
            int arrowY = y + CAR_HEIGHT / 2;
            DrawTriangle((Vector2){(float)arrowX, (float)arrowY},
                         (Vector2){(float)(arrowX + 8), (float)(arrowY - 6)},
                         (Vector2){(float)(arrowX + 8), (float)(arrowY + 6)},
                         TEXT_SECONDARY);
        }

        x += QUEUE_ITEM_WIDTH;
        current = current->next;
        ++count;
    }

    if (queue.getSize() > 7)
    {
        DrawText(TextFormat("+%d more", queue.getSize() - 7), x, y + 22, 14, TEXT_SECONDARY);
    }
}

void DrawParkingModern(const ParkingLot &lot, int highlightedStackId, const std::string &highlightedCarId)
{
    if (lot.getNumStacks() == 0)
        return;

    int stackMaxCapacity = lot.getStack(0)->getCapacity();
    int totalHeight = stackMaxCapacity * (CAR_HEIGHT + CAR_SPACING) + 50;
    int totalWidth = lot.getNumStacks() * (STACK_WIDTH + STACK_SPACING) + 40;

    Rectangle parkingPanel = {(float)(PARKING_START_X - 20), (float)(PARKING_START_Y - 80), (float)totalWidth, (float)(totalHeight + 80)};
    DrawRectangleRounded(parkingPanel, 0.08f, 8, BG_SECONDARY);
    DrawRectangleRoundedLines(parkingPanel, 0.08f, 8, 1, BG_TERTIARY);

    DrawText("PARKING LOT STACKS (LIFO)", PARKING_START_X + 4, PARKING_START_Y - 60, 22, TEXT_PRIMARY);

    int stackX = PARKING_START_X;
    for (int i = 0; i < lot.getNumStacks(); ++i)
    {
        StackLL *stack = lot.getStack(i);
        if (!stack)
        {
            stackX += STACK_WIDTH + STACK_SPACING;
            continue;
        }

        Rectangle laneRect = {(float)(stackX - 10), (float)(PARKING_START_Y - 20), (float)STACK_WIDTH, (float)totalHeight - 40};

        // panel for lane
        DrawRectangleRounded(laneRect, 0.06f, 8, BG_TERTIARY);
        DrawRectangleRoundedLines(laneRect, 0.06f, 8, 1, SURFACE);

        // Lane title
        std::string laneTitle = "LANE " + std::to_string(stack->getId());
        DrawText(laneTitle.c_str(), stackX + 4, PARKING_START_Y - 36, 16, TEXT_PRIMARY);

        // capacity badge with gentle color
        std::string capacity = std::to_string(stack->getSize()) + "/" + std::to_string(stack->getCapacity());
        Color capColor = stack->isFull() ? ACCENT_RED : fade(ACCENT_GREEN, 0.95f);
        Rectangle capBadge = {(float)stackX + 8, (float)PARKING_START_Y - 18, 74, 20};
        DrawRectangleRounded(capBadge, 0.35f, 6, capColor);
        int capWidth = MeasureText(capacity.c_str(), 12);
        DrawText(capacity.c_str(), capBadge.x + (capBadge.width - capWidth) / 2, capBadge.y + 3, 12, TEXT_PRIMARY);

        // draw empty spots outlines
        for (int j = 0; j < stackMaxCapacity; ++j)
        {
            int spotY = PARKING_START_Y + j * (CAR_HEIGHT + CAR_SPACING) + 10;
            Rectangle spot = {(float)(stackX + 10), (float)spotY, (float)CAR_WIDTH, (float)CAR_HEIGHT};
            DrawRectangleRoundedLines(spot, 0.12f, 6, 1, fade(SURFACE, 0.9f));
        }

        // draw cars from top (position 1 is top)
        Node *current = stack->getHead();
        int position = 1;
        while (current)
        {
            int carY = PARKING_START_Y + (position - 1) * (CAR_HEIGHT + CAR_SPACING) + 10;

            // decide highlight:

            bool highlightLane = (highlightedStackId > 0 && highlightedStackId == stack->getId());
            bool highlightCar = (!highlightedCarId.empty() && current->car && current->car->getId() == highlightedCarId && (highlightedStackId == -1 || highlightedStackId == stack->getId()));

            Color carColor = fade(ACCENT_BLUE, 1.0f - (float)position / (stackMaxCapacity * 2.5f)); // gentle depth effect
            DrawCarModern(current->car, stackX + 10, carY, carColor, highlightCar);

            // gentle lane highlight overlay for top area
            if (highlightLane)
            {
                Rectangle hl = {(float)(stackX + 10), (float)carY - 6, (float)CAR_WIDTH, (float)(CAR_HEIGHT + 6)};
                DrawRectangleRounded(hl, 0.12f, 6, (Color){ACCENT_BLUE.r, ACCENT_BLUE.g, ACCENT_BLUE.b, 28});
            }

            // mark TOP label
            if (position == 1)
            {
                DrawText("TOP", stackX - 34, carY + 14, 12, fade(ACCENT_GREEN, 0.9f));
            }

            current = current->next;
            ++position;
        }

        stackX += STACK_WIDTH + STACK_SPACING;
    }
}

// draws a modern soft button. Returns true when clicked (and not disabled).
bool DrawModernButton(Rectangle rect, const char *text, Color color, bool disabled)
{
    bool clicked = false;
    Color drawColor = disabled ? fade(SURFACE, 0.95f) : color;

    // hover lighten (soft)
    if (!disabled && CheckCollisionPointRec(GetMousePosition(), rect))
    {
        drawColor = fade(color, 1.08f);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            clicked = true;
    }

    // subtle shadow
    Rectangle shadow = {rect.x + 2, rect.y + 3, rect.width, rect.height};
    DrawRectangleRounded(shadow, 0.12f, 8, (Color){0, 0, 0, 48});

    // button background
    DrawRectangleRounded(rect, 0.12f, 8, drawColor);
    DrawRectangleRoundedLines(rect, 0.12f, 8, 1, fade(SURFACE, 0.95f));

    // text
    int fontSize = 15;
    int tw = MeasureText(text, fontSize);
    int tx = rect.x + (rect.width - tw) / 2;
    int ty = rect.y + (rect.height - fontSize) / 2;
    DrawText(text, tx, ty, fontSize, disabled ? TEXT_SECONDARY : TEXT_PRIMARY);

    return clicked && !disabled;
}

// a nicer textbox: bounds-check text length for visual fit and draws a blinking cursor.
void DrawModernTextBox(Rectangle rect, const char *text, bool editMode, const char *label)
{
    DrawText(label, rect.x, rect.y - 20, 14, TEXT_SECONDARY);

    Color bg = editMode ? BG_PRIMARY : BG_TERTIARY;
    DrawRectangleRounded(rect, 0.10f, 8, bg);
    DrawRectangleRoundedLines(rect, 0.10f, 8, 1, editMode ? fade(ACCENT_BLUE, 0.95f) : SURFACE);

    // compute max visible chars based on box width and average char width
    int avgCharW = MeasureText("W", 14);
    int padding = 12;
    int maxVisible = (int)((rect.width - padding * 2) / avgCharW);
    std::string txt = text ? text : std::string();
    if ((int)txt.size() > maxVisible)
    {
        // show trailing part
        txt = txt.substr(txt.size() - maxVisible);
    }

    DrawText(txt.c_str(), rect.x + padding, rect.y + (rect.height - 14) / 2, 14, TEXT_PRIMARY);

    // blinking cursor
    if (editMode && fmod(GetTime() * 2.0f, 1.0f) < 0.5f)
    {
        int cursorX = rect.x + padding + MeasureText(txt.c_str(), 14);
        DrawRectangle(cursorX, rect.y + 8, 2, rect.height - 16, TEXT_PRIMARY);
    }
}

// update textbox characters into buffer (maxChars includes null terminator)
void UpdateModernTextBox(Rectangle rect, char *text, bool &editMode, int maxChars)
{
    if (CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        editMode = true;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (!CheckCollisionPointRec(GetMousePosition(), rect))
            editMode = false;
    }

    if (!editMode)
        return;

    int key = GetCharPressed();
    while (key > 0)
    {
        if (key >= 32 && key <= 126 && (int)strlen(text) < maxChars - 1)
        {
            int len = (int)strlen(text);
            text[len] = (char)key;
            text[len + 1] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && strlen(text) > 0)
    {
        text[strlen(text) - 1] = '\0';
    }
}

void DrawOutputPanel(const std::string &message, int x, int y, int width)
{
    Rectangle panel = {(float)x, (float)y, (float)width, 84};
    DrawRectangleRounded(panel, 0.10f, 8, BG_TERTIARY);
    DrawRectangleRoundedLines(panel, 0.10f, 8, 1, SURFACE);

    // wrap text if too long (simple)
    int maxCharsPerLine = (width - 24) / MeasureText("a", 14);
    std::string msg = message;
    std::vector<std::string> lines;
    while (!msg.empty())
    {
        if ((int)msg.size() <= maxCharsPerLine)
        {
            lines.push_back(msg);
            break;
        }
        int cut = maxCharsPerLine;
        // prefer break at space
        for (int i = cut; i > 0; --i)
            if (msg[i] == ' ')
            {
                cut = i;
                break;
            }
        lines.push_back(msg.substr(0, cut));
        if ((int)msg.size() > cut)
            msg = msg.substr(cut + (msg[cut] == ' ' ? 1 : 0));
        else
            msg.clear();
    }

    int drawY = y + 10;
    for (size_t i = 0; i < lines.size() && i < 4; ++i)
    {
        DrawText(lines[i].c_str(), x + 12, drawY, 14, TEXT_PRIMARY);
        drawY += 18;
    }
}

void DrawTitle(const char *text, int x, int y)
{
    DrawText(text, x, y, TITLE_FONT_SIZE, ACCENT_BLUE);
}

void DrawSectionDivider(int y)
{
    DrawRectangle(UI_AREA_START_X, y, BUTTON_WIDTH, 2, SURFACE);
}
