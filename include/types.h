#ifndef TYPES
#define TYPES

#define WIDTH 800.0f
#define HEIGHT 450.0f
#define FLOOR_LEVEL 280.0f

#define ZOOM_DOWN_CAP 0.1f
#define ZOOM_UP_CAP 5.0f

#include <raylib.h>

typedef struct {
    Rectangle structure;
    Color color;
} Building;

typedef enum { Undefined = -1, MODE_GAME , MODE_MENU , MODE_END } GameMode;

#endif
