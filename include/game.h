#include <raylib.h>

extern int GOAL;

void makeMove(Rectangle *player, float delta) ;
void syncCamera(Rectangle *player, Camera2D *camera) ;
void detectPlayerMovement(Rectangle *playerModel, Camera2D *camera);
