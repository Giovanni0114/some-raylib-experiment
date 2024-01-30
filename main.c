#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "drawing.c"
#include "game.c"
#include "menu.c"
#include "music.c"

int NUM_BUILDINGS = -1;
int points = 0;
float building_offset = 0;

struct timeval timeStart, timeEnd;

Camera2D camera = {};
Rectangle playerModel = {};
Rectangle floorModel = {};
Building buildings[240];
Building *corruptedBuildings[15];
Color currentBackground = RAYWHITE;
GameMode gameMode = MODE_GAME;

float calculateTime(struct timeval start, struct timeval end){
    float seconds  = end.tv_sec  - start.tv_sec;
    float useconds = end.tv_usec - start.tv_usec;

     return (seconds + useconds/1000000.0);
}    

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
                    gettimeofday(&timeEnd, NULL);
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
            showEndScreen(points, calculateTime(timeStart, timeEnd));
            break;
    }

#ifdef DEBUG_LINES
    DrawLine(WIDTH / 2, HEIGHT, WIDTH / 2, 0, RED);
    DrawLine(0, HEIGHT/2, WIDTH, HEIGHT/2, RED);
#endif 

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
        default:
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
    gettimeofday(&timeStart, NULL);
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        struct timeval curTime;
        gettimeofday(&curTime, NULL);

        double stats[] = {camera.zoom, (float)gameMode, curTime.tv_sec, curTime.tv_usec/1000000.0, calculateTime(timeStart, curTime)};

        _preDrawing();
        BeginDrawing();
        _pre2DMode();
        BeginMode2D(camera);
        _mainEventLoop();
        EndMode2D();
        _post2DMode();
        showStats(stats, 0);
        EndDrawing();
        _postDrawing();
    }

    return EXIT_SUCCESS;
}
