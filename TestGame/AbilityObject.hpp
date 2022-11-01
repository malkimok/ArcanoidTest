#include "MovingObject.hpp"
#pragma once

enum class AbilityType{
    SavingWall,
    DamageDeal
};

class AbilityObject: public MovingObject{
public:
    inline static const float basicSpeed = 150;
    inline static int DDsCaught = 0;
    AbilityType abType;
    using MovingObject::MovingObject;
    static void spawnAbility(float x, float y);
    static AbilityObject* createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection, AbilityType type);
    void useAbility();
    void doWhenCollide();
};
