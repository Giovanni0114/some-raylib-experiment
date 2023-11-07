#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Rectangle structure;
    Color color;
} Building;

void makeMove(Rectangle *player, float delta) { player->x += delta; }

void syncCamera(Rectangle *player, Camera2D *camera) { camera->target = (Vector2){player->x + 20, player->y + 20}; }

int main(int argc, char *argv[]) {
    const int WIDTH = 800;
    const int HEIGHT = 450;
    int NUM_BUILDINGS = 0;
    float SPEED = 5;

    InitWindow(WIDTH, HEIGHT, "o ja pierdolę!");
    SetExitKey(KEY_Q);
    SetTargetFPS(60);

    Rectangle player = {400, 280, 40, 40};
    Rectangle floor = {-6000, 320, 12000, 1000};
    Building *buildings = malloc(240 * sizeof(Building));

    float spacing = 0;

    while (spacing < 12000.0) {
        Rectangle this;
        this.width = (float)GetRandomValue(50, 100);
        this.height = (float)GetRandomValue(100, 800);
        this.y = HEIGHT - 130.0 - this.height;
        this.x = -6000.0 + spacing;

        spacing += this.width;

        buildings[NUM_BUILDINGS++] = (Building){
            this, (Color){GetRandomValue(200, 240), GetRandomValue(200, 240), GetRandomValue(200, 250), 255}};
    }

    // printf("%f %f\n", buildings[1].structure.height, buildings[1].structure.width);
    // printf("%f %f\n", buildings[3].structure.height, buildings[3].structure.width);
    // printf("%f %f\n", buildings[6].structure.height, buildings[6].structure.width);
    // printf("%f %f\n", buildings[8].structure.height, buildings[8].structure.width);
    // printf("%f %f\n", buildings[10].structure.height, buildings[10].structure.width);

    Camera2D camera = {};
    camera.target = (Vector2){player.x + 20, player.y + 20};
    camera.offset = (Vector2){(float)WIDTH / 2, (float)HEIGHT / 2};
    camera.rotation = 0;
    camera.zoom = 0.05;

    while (!WindowShouldClose()) {
        // Player move
        if (IsKeyDown(KEY_RIGHT)) {
            makeMove(&player, SPEED);
        }
        if (IsKeyDown(KEY_LEFT)) {
            makeMove(&player, -SPEED);
        }
        // Player move
        if (IsKeyDown(KEY_UP)) {
            camera.zoom *= 1.05;
        }
        if (IsKeyDown(KEY_DOWN)) {
            camera.zoom /= 1.05;
        }

        SPEED = IsKeyDown(KEY_SPACE) ? 25 : 5;

        if (player.x > 6020 || player.x < -6000) {
            player.y += 10;
        }
        else if (player.y > 280) {
            player.y -= 10;
        }
        else {
            player.y = 280;
        }

        syncCamera(&player, &camera);
        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        // Draw
        for (int i = 0; i < NUM_BUILDINGS; i++) {
            DrawRectangleRec(buildings[i].structure, buildings[i].color);
        }
        DrawRectangleRec(floor, DARKGRAY);
        DrawRectangleRec(player, RED);

        EndMode2D();
        EndDrawing();
    }

    return EXIT_SUCCESS;
}
