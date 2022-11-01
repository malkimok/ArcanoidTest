#include "inc/Framework.h"
#include "vec2.hpp"
#include <vector>

#pragma once

using namespace std;

class Object{
protected:
//    inline static vector<Object*> allObjectsVec = vector<Object*>(); // vector<Object*>()
    vec2<float> coordinates;
    int width;
    int height;
    Sprite* objSprite;
    
public:
    Object() = default;
    virtual ~Object() = default;
    virtual void doWhenCollide();
    Object(float x, float y, int width, int height);
    Object* createObject(float x, float y, int width, int height, const char* path);
    void attachSprite(const char* path);
    bool isColliding(Object* potentiallyCollidingObj);
    bool verticalReflection(Object* collidingObj);
    
    Sprite* getObjSprite();
    const float eps = 3;
    float getX();
    float getY();
    int getWidth();
    int getHeight();
};
