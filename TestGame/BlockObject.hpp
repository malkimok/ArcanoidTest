#include "MovingObject.hpp"
#pragma once

class BlockObject: public MovingObject{
public:
    using MovingObject::MovingObject;
    void createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection);
    void doWhenCollide();
};
