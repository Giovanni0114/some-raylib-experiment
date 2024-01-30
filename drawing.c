#pragma once

#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "rlgl.h"
#include "types.h"

typedef enum {
    BSTATE_NONE = 0x0,
    BSTATE_ABOVE = 0x1,
    BSTATE_CLICKED = 0x2,
    BSTATE_FOCUS = 0x4,
} ButtonState;

Color getColorForGameMode(const GameMode mode) {
    switch (mode) {
        case MODE_GAME:
            return RAYWHITE;
        case MODE_MENU:
            return LIGHTGRAY;
        case MODE_END:
            return BEIGE;
        case Undefined:
        default:
            assert(false);
    }
}

void DrawTextCenter(char *text, int poz_x, int poz_y, int fontSize, Color color) {
    DrawText(text, poz_x - (int)(MeasureText(text, fontSize) / 2), poz_y - fontSize / 2, fontSize, color);
}

bool isCursorAboveRectangle(Rectangle rectangle) {
    int x = GetMouseX();
    int y = GetMouseY();
    bool ret = true;

    ret &= x > rectangle.x;
    ret &= x < rectangle.x + rectangle.width;

    ret &= y > rectangle.y;
    ret &= y < rectangle.y + rectangle.height;

    if (ret) SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    return ret;
}

bool button(char *text, float poz_x, float poz_y, float width, float height) {
    Rectangle rec = {poz_x, poz_y, width, height};

    DrawRectangleRec(rec, isCursorAboveRectangle(rec) ? SKYBLUE : BLUE);
    DrawTextCenter(text, poz_x + (width / 2), poz_y + (height / 2), (int)(height * 0.75),
                   isCursorAboveRectangle(rec) ? BLACK : RAYWHITE);

    return isCursorAboveRectangle(rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
void drawBackground(const GameMode gameMode) {
    ClearBackground(getColorForGameMode(gameMode));

    if (gameMode != MODE_GAME) return;

    rlPushMatrix();
    {  // In matrix pushed
        rlTranslatef(0, 200 * 50, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(1000 * 8, 10);
    }
    rlPopMatrix();
}

bool checkIfCorrupted(Building *building, Rectangle *playerModel) {
    return building != NULL && building->structure.x < playerModel->x + 20
           && building->structure.x + building->structure.width > playerModel->x + 20;
}
void showScore(int point) {
    char score[15];
    sprintf(score, "Points: %d", point);
    DrawText(score, 20, 20, 20, GREEN);
}

void showStats(double *stats, int len) {
    char buffer[15];
    for (int i = 0; i < len; i++) {
        sprintf(buffer, "%.4f", stats[i]);
        DrawText(buffer, 20, HEIGHT - 20 * (i + 1), 20, RED);
    }
}

void showEndScreen(int _score, float _timeSec) {
    char score[100];

    sprintf(score, "Points: %d  Time: %.2f", _score, _timeSec);

    DrawText(score, 20, HEIGHT - 50, 32, BROWN);

    DrawTextCenter("THE END", WIDTH / 2, HEIGHT / 2, 64, DARKBROWN);
}
