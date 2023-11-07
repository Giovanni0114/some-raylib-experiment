#define RAYGUI_IMPLEMENTATION

#include <assert.h>
#include <stdio.h>

#include "raygui.h"
#include "raylib.h"

int WIDTH = 950, HEIGHT =550;
int buttonsNumber = 0;

void makeGrid() {
    assert(IsWindowReady());
    // printf("makeGrid start\n");

    for (int i = 1; i < WIDTH * 2 / 100; i++) {
        DrawLineV((Vector2){50.0f * i, 0.0f}, (Vector2){50.0f * i, HEIGHT}, RAYWHITE);
    }
    for (int i = 1; i < HEIGHT * 2 / 100; i++) {
        DrawLineV((Vector2){0.0f, 50.0f * i}, (Vector2){WIDTH, 50.0f * i}, RAYWHITE);
    }
}

void makeMenu(){
    if (GuiButton((Rectangle){49, 49, 101, 51}, "Add")) {
        buttonsNumber++;
    }
    if (GuiButton((Rectangle){199, 49, 101, 51}, "Subtract")) {
        if (buttonsNumber != 0) buttonsNumber--;
    }
    if (GuiButton((Rectangle){549, 49, 51, 51}, "+ H")) {
        HEIGHT += 50;
    }
    if (GuiButton((Rectangle){699, 49, 51, 51}, "- H")) {
        HEIGHT -= 50;
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    char str[3];
    sprintf(str, "%d", buttonsNumber);
    DrawText(str, 349 + 25 - strlen(str)*8, 49+10, 30, RAYWHITE);
}

void drawSquares(int number) {
    int rows = number / 9;
    int j;
    for (j = 0; j < rows; j++) {
        for (int i = 0; i < 9; i++) {
            DrawRectangleRec((Rectangle){49 + (i * 100), 149 + (j * 100), 50, 50}, RAYWHITE);
        }
    }
    for (int i = 0; i < number - (rows * 9); i++) {  // last row
        DrawRectangleRec((Rectangle){49 + (i * 100), 149 + (j * 100), 50, 50}, RAYWHITE);
    }
}

int main() {

        InitWindow(WIDTH, HEIGHT, "Test test");
        SetTargetFPS(60);
    // makeGrid();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawFPS(0, 0);
        makeGrid();
        makeMenu();
        drawSquares(buttonsNumber);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
