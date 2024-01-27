#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "rlgl.h"
#include "types.h"

Color getColorForGameMode(const GameMode mode){
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

void showStats(float *stats, int len){
    char buffer[15];
    for (int i = 0; i < len; i++){
        sprintf(buffer, "%f", stats[i]);
        DrawText(buffer, 20, HEIGHT - 20 * (i+1), 20, RED);
    }
}

void showEndScreen(int _score, float _timeS){
    char score[5];
    char time[10];

    sprintf(score, "%d", _score);
    sprintf(time, "%f", _timeS);

    DrawText(score, 20, 20, 20, GREEN);
    DrawText(time, 20, 20, 20, GREEN);

} 



