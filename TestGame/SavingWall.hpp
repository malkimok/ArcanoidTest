#include "WallObject.hpp"

#pragma once

class SavingWall: public WallObject{
public:
    using WallObject::WallObject;
    const float lifeTime = 10; //10 sec
    float appeared = 0;
    static void createObject(float x, float y, int width, int height, const char* path);
    void destroyWall();
};
