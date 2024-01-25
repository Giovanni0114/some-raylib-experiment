#ifndef TYPES
#define TYPES

#include <raylib.h>

const float WIDTH = 800;
const float HEIGHT = 450;
const float FLOOR_LEVEL = 280.0;

const float ZOOM_DOWN_CAP = 0.1;
const float ZOOM_UP_CAP = 5;

typedef struct {
    Rectangle structure;
    Color color;
} Building;

typedef enum {
    Undefined = -1,
    MODE_GAME = 0,
    MODE_MENU = 1,
    MODE_END = 2
} GameMode;

#endif
