#include <raylib.h>

Music music = {};
float musicLevel = 0.25;

void initMusic(){
    music = LoadMusicStream("music/ambient.mp3");
    SetMusicVolume(music, musicLevel);
}

void getVolumeFrom100(int level){
    SetMusicVolume(music, (float)level/100);
}
