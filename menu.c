#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*FunctionPointer)();
typedef struct MenuObject{
    char name[15];
    char displayName[30];
    FunctionPointer function;
} Menu;

// MENU ELEMENT START
#define _X(x) (x + 370)
#define _Y(y) (y + 20)

void drawAvatarMenu(){
    // color picker
};

void drawVolumeMenu(){
    
};
void drawGameSettingsMenu(){};
void drawCreditsMenu(){
    DrawText("WWWWWW", _X(20), _Y(20), 24, BLACK);
};

char activeObject[15] = {};

const struct MenuObject menuObjects[] = {
    {"avatar", "Avatar appearance", drawAvatarMenu},
    {"volume","Volume", drawVolumeMenu},
    {"game-settings","Game Settings", drawGameSettingsMenu},
    {"credits", "Credits", drawCreditsMenu},
};

const struct MenuObject* lookupObjects(const char name[15]){
    for (int i = 0; i < sizeof(menuObjects)/sizeof(struct MenuObject); i++) {
        if (menuObjects[i].name == name) {
            return (menuObjects + i);
        }
    }
    return NULL;
};

bool isCursorAboveMenuObject(int idx){
    int x = GetMouseX(); int y = GetMouseY();
    bool ret = true;
    ret &= x > 20;
    ret &= x < 350;
    ret &= y > 40 + (idx*50);
    ret &= y < 40 + (idx*50) + 40;
    if (ret) SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    return ret;
}

void showMenu(){
    bool isCursorAboveNoneBlocks = false;

    for (int i = 0; i < sizeof(menuObjects)/sizeof(struct MenuObject); i++) {
        if (isCursorAboveMenuObject(i)){
            isCursorAboveNoneBlocks = true;
        }
        DrawRectangle(20, 40 + (i*50), 330, 40, isCursorAboveMenuObject(i)?SKYBLUE:BLUE);
        DrawText(menuObjects[i].displayName, 30, 45 + (i*50), 30, RAYWHITE);
    }

    DrawLine(370, 20, 370, 430, RED);
    DrawLine(770, 20, 770, 430, RED);


    if (!isCursorAboveNoneBlocks){
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

