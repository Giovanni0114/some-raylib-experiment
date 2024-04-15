#include "drawing.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

bool resetCursor = false;

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
    DrawText(text, poz_x - MeasureText(text, fontSize) / 2, poz_y - fontSize / 2, fontSize, color);
}

bool isCursorAboveRectangle(Rectangle rectangle) {
    Vector2 pos = GetMousePosition();
    bool ret = true;

    ret &= pos.x > rectangle.x;
    ret &= pos.x < rectangle.x + rectangle.width;

    ret &= pos.y > rectangle.y;
    ret &= pos.y < rectangle.y + rectangle.height;

    if (ret) SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    return ret;
}

bool createButton(char *text, float poz_x, float poz_y, float width, float height) {
    Rectangle rec = {poz_x, poz_y, width, height};

    DrawRectangleRec(rec, isCursorAboveRectangle(rec) ? SKYBLUE : BLUE);
    DrawTextCenter(text, poz_x + (width / 2), poz_y + (height / 2), (int)(height * 0.75),
                   isCursorAboveRectangle(rec) ? BLACK : RAYWHITE);

    if (isCursorAboveRectangle(rec)){
        resetCursor = false;
        SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    }
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
    char *score;
    asprintf(&score, "Points: %d", point);
    DrawText(score, 20, 20, 20, GREEN);
    free(score);
}

void showStats(double *stats, int len) {
    char *buffer;
    for (int i = 0; i < len; i++) {
        asprintf(&buffer, "%.4f", stats[i]);
        DrawText(buffer, 20, (int)HEIGHT - 20 * (i + 1), 20, RED);
        free(buffer);
    }
}

void showEndScreen(int _score, float _timeSec) {
    char *score;
    asprintf(&score, "Points: %d  Time: %.2f", _score, _timeSec);

    DrawText(score, 20, (int)HEIGHT - 50, 32, BROWN);
    free(score);

    DrawTextCenter("THE END", (int)WIDTH / 2, (int)HEIGHT / 2, 64, DARKBROWN);

    if (createButton("REMATCH", WIDTH * 3 / 5, HEIGHT - 100, 220, 46)) {
        printf("unimplemented");
    }
}

void tryResetCursor(){
    if (resetCursor) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    resetCursor = true;
}

