#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "rlgl.h"
#include "types.h"

const float WIDTH = 800;
const float HEIGHT = 450;
const float FLOOR_LEVEL = 280.0;

const float ZOOM_DOWN_CAP = 0.1;
const float ZOOM_UP_CAP = 5;

int NUM_BUILDINGS = -1;
int points = 0;

float SPEED = 5;
float building_offset = 0;

Camera2D camera = {};
Rectangle playerModel = {};
Rectangle floorModel = {};
Building buildings[240];
Building *corruptedBuildings[15];

void makeMove(Rectangle *player, float delta) { player->x += delta; }

void syncCamera(Rectangle *player, Camera2D *camera) { camera->target = (Vector2){player->x + 20, player->y + 20}; }

void drawBackground() {
    ClearBackground(RAYWHITE);
    rlPushMatrix();
    {  // In matrix pushed
        rlTranslatef(0, 200 * 50, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(1000 * 8, 10);
    }
    rlPopMatrix();
}

bool checkIfCorrupted(Building *building) {
    return building != NULL && building->structure.x < playerModel.x + 20
           && building->structure.x + building->structure.width > playerModel.x + 20;
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

void _preDrawing() {
    SPEED = IsKeyDown(KEY_SPACE) ? 25 : 5;

    // Player move
    if (IsKeyDown(KEY_RIGHT)) {
        makeMove(&playerModel, SPEED);
    }
    if (IsKeyDown(KEY_LEFT)) {
        makeMove(&playerModel, -SPEED);
    }
    // Player move
    if (IsKeyDown(KEY_UP)) {
        if (camera.zoom <= ZOOM_UP_CAP) {
            camera.zoom *= 1.05;
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        if (camera.zoom >= ZOOM_DOWN_CAP) {
            camera.zoom /= 1.05;
        }
    }

    if (IsKeyDown(KEY_A)) {
        int i = 0, target = -1;
        for (; i < 15; i++) {
            if (checkIfCorrupted(corruptedBuildings[i])) {
                corruptedBuildings[i]->color = GREEN;
                corruptedBuildings[i] = NULL;
                points++;
                break;
            }
        }
    }
    // Set speed
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
    showScore(points); 
}

void _mainEventLoop() {
    drawBackground();
    for (int i = 0; i <= NUM_BUILDINGS; i++) {
        DrawRectangleRec(buildings[i].structure, buildings[i].color);
    }
    DrawRectangleRec(floorModel, DARKGRAY);
    DrawRectangleRec(playerModel, RED);
}

int main(int argc, char *argv[]) {
    playerModel = (Rectangle){400, FLOOR_LEVEL, 40, 40};
    floorModel = (Rectangle){-6000, 320, 12000, 1000};

    InitWindow((int)WIDTH, (int)HEIGHT, "o ja pierdolę!");
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

    while (!WindowShouldClose()) {
        float stats[] = {camera.zoom};

        _preDrawing();
        BeginDrawing();
        _pre2DMode();
        BeginMode2D(camera);
        _mainEventLoop();
        EndMode2D();
        _post2DMode();
        showStats(stats, 1);
        EndDrawing();
        _postDrawing();
    }

    return EXIT_SUCCESS;
}
