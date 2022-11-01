#include "BallObject.hpp"

BallObject* BallObject::createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection){
    BallObject* obj = new BallObject(x, y, width, height, speed, mDirection);
    obj->attachSprite(path);
    return obj;
}
