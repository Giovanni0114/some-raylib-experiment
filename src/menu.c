#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

// MENU ELEMENT RELATIVE POSITIONS
#define MENU_X(x) ((x) + 370)
#define MENU_Y(y) ((y) + 20)

FunctionPointer activeMenuObjectFunction = NULL;

const MenuObject s_menuObjects[] = {
    {"avatar", "Avatar appearance", drawAvatarMenu},
    {"volume", "Volume", drawVolumeMenu},
    {"game-settings", "Game Settings", drawGameSettingsMenu},
    {"credits", "Credits", drawCreditsMenu},
    {"exit", "Exit", exitGame},
};

void drawAvatarMenu() {
    DrawText("drawAvatarMenu()", MENU_X(20), MENU_Y(20), 28, RED);
};

void drawVolumeMenu() {
    DrawText("drawVolumeMenu()", MENU_X(20), MENU_Y(20), 28, RED);
};

void drawGameSettingsMenu() {
    DrawText("drawGameSettingsMenu()", MENU_X(20), MENU_Y(20), 28, RED);
};

void drawCreditsMenu() {
    DrawText("Author:", MENU_X(20), MENU_Y(20), 28, RED);
    DrawText("giovanni", MENU_X(30), MENU_Y(52), 24, BLACK);
    DrawText("<janko.juroszek@gmail.com>", MENU_X(30), MENU_Y(75), 24, BLACK);
};

void exitGame() {
    exit(0);
}

const MenuObject *lookupObjects(const char name[15]) {
    for (unsigned int i = 0; i < sizeof(s_menuObjects) / sizeof(MenuObject); i++) {
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
    return ret;
}

void showMenu() {
    for (uint i = 0; i < sizeof(s_menuObjects) / sizeof(MenuObject); i++) {
        if (createButton(s_menuObjects[i].displayName, 20, 40 + (i * 50), 330, 40)) {
            if (activeMenuObjectFunction == NULL || activeMenuObjectFunction != s_menuObjects[i].function) {
                activeMenuObjectFunction = s_menuObjects[i].function;
            } else {
                activeMenuObjectFunction = NULL;
            }
        }
    }

    DrawLine(370, 20, 370, 430, RED);
    DrawLine(770, 20, 770, 430, RED);

    if (activeMenuObjectFunction == NULL) {
        return;
    }

    activeMenuObjectFunction();
}
