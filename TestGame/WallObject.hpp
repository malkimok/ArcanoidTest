#include "Object.hpp"
#pragma once

class WallObject: public Object{
public:
    using Object::Object;
    static void createObject(float x, float y, int width, int height, const char* path);
};
