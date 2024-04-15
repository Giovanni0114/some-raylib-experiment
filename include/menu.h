#include <stdio.h>
#include <stdlib.h>

#include "drawing.h"

typedef void (*FunctionPointer)(void);
typedef struct {
    char *name;
    char *displayName;
    FunctionPointer function;
} MenuObject;

extern FunctionPointer activeMenuObjectFunction;

void drawAvatarMenu();
void drawVolumeMenu();
void drawGameSettingsMenu();
void drawCreditsMenu();

void exitGame() ;

const MenuObject *lookupObjects(const char name[15]);

bool isCursorAboveMenuObject(int idx);

void showMenu();
