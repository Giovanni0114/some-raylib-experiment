#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "drawing.c"
#include "game.c"
#include "menu.c"
#include "music.c"

int NUM_BUILDINGS = -1;
int points = 0;
float building_offset = 0;

Camera2D camera = {};
Rectangle playerModel = {};
Rectangle floorModel = {};
Building buildings[240];
Building *corruptedBuildings[15];
Color currentBackground = RAYWHITE;
GameMode gameMode = MODE_GAME;

void _preDrawing() {
    if (gameMode == MODE_GAME) {
        detectPlayerMovement(&playerModel, &camera);

        if (IsKeyDown(KEY_A)) {
            for (int i = 0; i < 15; i++) {
                if (!checkIfCorrupted(corruptedBuildings[i], &playerModel)) {
                    continue;
                }

                corruptedBuildings[i]->color = GREEN;
                corruptedBuildings[i] = NULL;
                if (++points == GOAL) { 
                    gameMode = MODE_END;
                }
                break;
            }
        }
    }

    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_CAPS_LOCK)) {
        if (gameMode == MODE_GAME) {
            gameMode = MODE_MENU;
        } else {
            gameMode = MODE_GAME;
        }
    }

    if (playerModel.x > 6020 || playerModel.x < -6000) {
        playerModel.y += 10;
    } else if (playerModel.y > FLOOR_LEVEL) {
        playerModel.y -= 10;
    } else if (playerModel.y != FLOOR_LEVEL) {
        playerModel.y = FLOOR_LEVEL;  // floor level
    }
    syncCamera(&playerModel, &camera);
}

void _postDrawing() {}
void _pre2DMode() {}

void _post2DMode() {
    switch (gameMode) {
        case Undefined:
            assert(false);

        case MODE_GAME:
            showScore(points);
            break;

        case MODE_MENU:
            showMenu();
            break;

        case MODE_END:
            showMenu();
            break;
    }
}

void _mainEventLoop() {
    drawBackground(gameMode);
    switch (gameMode) {
        case Undefined:
            assert(false);

        case MODE_GAME:
            for (int i = 0; i <= NUM_BUILDINGS; i++) {
                DrawRectangleRec(buildings[i].structure, buildings[i].color);
            }
            DrawRectangleRec(floorModel, DARKGRAY);
            DrawRectangleRec(playerModel, RED);
            break;

        case MODE_MENU:
        case MODE_END:
            break;
    }
}

int main() {
    playerModel = (Rectangle){400, FLOOR_LEVEL, 40, 40};
    floorModel = (Rectangle){-6000, 320, 12000, 5000};

    InitWindow((int)WIDTH, (int)HEIGHT, "City cleaner");
    InitAudioDevice();
    initMusic();
    SetExitKey(KEY_Q);
    SetTargetFPS(60);

    while (building_offset < 12000.0) {
        Rectangle this;
        this.width = (float)GetRandomValue(50, 100);
        this.height = (float)GetRandomValue(100, 800);
        this.y = HEIGHT - 130.0 - this.height;
        this.x = -6000.0 + building_offset;

        building_offset += this.width;

        buildings[++NUM_BUILDINGS] = (Building){
            this, (Color){GetRandomValue(200, 240), GetRandomValue(200, 240), GetRandomValue(200, 250), 255}};
    }

    assert(NUM_BUILDINGS != -1);
    if (buildings[NUM_BUILDINGS].structure.x + buildings[NUM_BUILDINGS].structure.width > 6000) {
        buildings[NUM_BUILDINGS].structure.width = 6000.0 - buildings[NUM_BUILDINGS].structure.x;
    }

    // printf("%f %f\n", buildings[NUM_BUILDINGS].structure.x, buildings[NUM_BUILDINGS].structure.width);
    // printf("%f %f\n", buildings[6].structure.height, buildings[6].structure.width);
    // printf("%f %f\n", buildings[8].structure.height, buildings[8].structure.width);
    // printf("%f %f\n", buildings[10].structure.height, buildings[10].structure.width);

    camera.target = (Vector2){playerModel.x + 20, playerModel.y + 20};
    camera.offset = (Vector2){(float)WIDTH / 2, (float)HEIGHT / 2 + 70};
    camera.rotation = 0;
    camera.zoom = 0.40;

    // make corrupted buildings
    for (int i = 0; i < 15; i++) {
        int idx = GetRandomValue(0, NUM_BUILDINGS);
        corruptedBuildings[i] = &buildings[idx];
        corruptedBuildings[i]->color = PURPLE;
    }
    PlayMusicStream(music);
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        float stats[] = {camera.zoom, (float)gameMode};

        _preDrawing();
        BeginDrawing();
        _pre2DMode();
        BeginMode2D(camera);
        _mainEventLoop();
        EndMode2D();
        _post2DMode();
        showStats(stats, 2);
        EndDrawing();
        _postDrawing();
    }

    return EXIT_SUCCESS;
}
