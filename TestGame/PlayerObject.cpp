#include "PlayerObject.hpp"
#include "MyFramework.hpp"

PlayerObject* PlayerObject::createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection){
    PlayerObject* obj = new PlayerObject(x, y, width, height, speed, mDirection);
    obj->attachSprite(path);
    return obj;
}


