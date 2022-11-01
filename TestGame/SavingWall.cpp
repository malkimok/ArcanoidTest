#include "SavingWall.hpp"
#include "MyFramework.hpp"
#include <time.h>

void SavingWall::createObject(float x, float y, int width, int height, const char* path){
    SavingWall* obj = new SavingWall(x, y, width, height);
    obj->attachSprite(path);
    obj->appeared = clock();
    MyFramework::allSavingWalls.push_back(obj);
}

void SavingWall::destroyWall(){
    coordinates.x = -1000;
    coordinates.y = -1000;
    MyFramework::allSavingWalls.remove(this);
}
