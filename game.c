#include <raylib.h>
#include "types.h"

int GOAL = 5;

void makeMove(Rectangle *player, float delta) { player->x += delta; }
void syncCamera(Rectangle *player, Camera2D *camera) { camera->target = (Vector2){player->x + 20, player->y + 20}; }
void detectPlayerMovement(Rectangle *playerModel, Camera2D *camera){
    int SPEED = IsKeyDown(KEY_SPACE) ? 25 : 5;
    if (IsKeyDown(KEY_RIGHT)) {
        makeMove(playerModel, SPEED);
    }
    if (IsKeyDown(KEY_LEFT)) {
        makeMove(playerModel, -SPEED);
    }
    if (IsKeyDown(KEY_UP)) {
        if (camera->zoom <= ZOOM_UP_CAP) {
            camera->zoom *= 1.05;
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        if (camera->zoom >= ZOOM_DOWN_CAP) {
            camera->zoom /= 1.05;
        }
    }

}
