#pragma once

#include <raylib.h>

#include "rlgl.h"
#include "types.h"

extern bool resetCursor;

typedef enum {
    BSTATE_NONE = 0x0,
    BSTATE_ABOVE = 0x1,
    BSTATE_CLICKED = 0x2,
} ButtonState;

Color getColorForGameMode(GameMode mode);

bool checkIfCorrupted(Building *building, Rectangle *playerModel);
bool createButton(char *text, float poz_x, float poz_y, float width, float height);
bool isCursorAboveRectangle(Rectangle rectangle);

void DrawTextCenter(char *text, int poz_x, int poz_y, int fontSize, Color color);
void drawBackground(GameMode gameMode);

void showEndScreen(int _score, float _timeSec);
void showScore(int point);
void showStats(double *stats, int len);

void tryResetCursor();
