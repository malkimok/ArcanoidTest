#include "WallObject.hpp"
#include "MyFramework.hpp"
#include "iostream"

void WallObject::createObject(float x, float y, int width, int height, const char* path){
    WallObject* obj = new WallObject(x, y, width, height);
    obj->attachSprite(path);
    MyFramework::allWalls.push_back(obj);
}
