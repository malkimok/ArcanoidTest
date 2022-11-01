#include "MovingObject.hpp"
#pragma once

class PlayerObject: public MovingObject{
public:
    using MovingObject::MovingObject;
    PlayerObject* createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection);
};
