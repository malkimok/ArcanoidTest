#include "MovingObject.hpp"
#pragma once

class BallObject: public MovingObject{
public:
    using MovingObject::MovingObject;
    BallObject* createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection);
};
