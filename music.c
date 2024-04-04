#include "music.h"
#include <raylib.h>

Music music = {};
float musicLevel = 0.05F;

void initMusic(){
    music = LoadMusicStream("music/ambient.mp3");
    SetMusicVolume(music, musicLevel);
}

void getVolumeFrom100(int level){
    SetMusicVolume(music, (float)level/100);
}
