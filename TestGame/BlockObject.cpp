#include "BlockObject.hpp"
#include "MyFramework.hpp"
#include "AbilityObject.hpp"
#include "iostream"

void BlockObject::createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection){
    BlockObject* obj = new BlockObject(x, y, width, height, speed, mDirection);
    obj->attachSprite(path);
    MyFramework::allObjectsToCollideVec.push_back(obj);
    MyFramework::allBlocksList.push_back(obj);
}

void BlockObject::doWhenCollide(){
    AbilityObject::spawnAbility(coordinates.x, coordinates.y);
    coordinates.x = -100;
    coordinates.y = -100;
    MyFramework::allBlocksList.remove(this);
}
