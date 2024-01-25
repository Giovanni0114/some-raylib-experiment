#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*FunctionPointer)(void);
typedef struct {
    char name[15];
    char displayName[30];
    FunctionPointer function;
} MenuObject;

// MENU ELEMENT START
#define _X(x) (x + 370)
#define _Y(y) (y + 20)

FunctionPointer activeMenuObjectFunction = NULL;

void drawAvatarMenu(){
    // color picker
};

void drawVolumeMenu(){

};
void drawGameSettingsMenu(){};
void drawCreditsMenu() { 
    DrawText("Author:", _X(20), _Y(20), 24, BLACK); 
    DrawText("giovanni", _X(30), _Y(50), 24, BLACK); 
    DrawText("<janko.juroszek@gmail.com>", _X(30), _Y(75), 24, BLACK); 
};
void exitGame() {
    exit(0);
}


char activeObject[15] = {};

const MenuObject s_menuObjects[] = {
    {"avatar", "Avatar appearance", drawAvatarMenu},
    {"volume", "Volume", drawVolumeMenu},
    {"game-settings", "Game Settings", drawGameSettingsMenu},
    {"credits", "Credits", drawCreditsMenu},
    {"exit", "Exit", exitGame},
};

const MenuObject* lookupObjects(const char name[15]) {
    for (uint i = 0; i < sizeof(s_menuObjects) / sizeof(MenuObject); i++) {
        if (s_menuObjects[i].name == name) {
            return &(s_menuObjects[i]);
        }
    }
    return NULL;
};

bool isCursorAboveMenuObject(int idx) {
    int x = GetMouseX();
    int y = GetMouseY();
    bool ret = true;
    ret &= x > 20;
    ret &= x < 350;
    ret &= y > 40 + (idx * 50);
    ret &= y < 40 + (idx * 50) + 40;
    if (ret) SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    return ret;
}

void showMenu() {
    bool isCursorAboveNoneBlocks = true;

    for (uint i = 0; i < sizeof(s_menuObjects) / sizeof(MenuObject); i++) {
        DrawRectangle(20, 40 + (i * 50), 330, 40, isCursorAboveMenuObject(i) ? SKYBLUE : BLUE);
        DrawText(s_menuObjects[i].displayName, 30, 45 + (i * 50), 30, RAYWHITE);

        if (isCursorAboveMenuObject(i)) {
            isCursorAboveNoneBlocks = false;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (activeMenuObjectFunction == NULL || activeMenuObjectFunction != s_menuObjects[i].function) {
                    activeMenuObjectFunction = s_menuObjects[i].function;
                } else {
                    activeMenuObjectFunction = NULL;
                }
            }
        }
    }

    DrawLine(370, 20, 370, 430, RED);
    DrawLine(770, 20, 770, 430, RED);

    if (isCursorAboveNoneBlocks) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (activeMenuObjectFunction == NULL) {
        return;
    }

    activeMenuObjectFunction();
}

