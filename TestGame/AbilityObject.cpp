#include "AbilityObject.hpp"
#include "MyFramework.hpp"
#include "SavingWall.hpp"

#include <cstdlib>
#include <iostream>

AbilityObject* AbilityObject::createObject(float x, float y, int width, int height, const char* path, float speed, vec2<float> mDirection, AbilityType type){
    AbilityObject* obj = new AbilityObject(x, y, width, height, speed, mDirection);
    obj->abType = type;
    obj->attachSprite(path);
    MyFramework::allAbilitiesList.push_back(obj);
    return obj;
}

// 40 out of 100 - damage, 4 out of 100 - sWall, 56 - nothing
void AbilityObject::spawnAbility(float x, float y){
    int rValue = std::rand() % 100 + 1; //random from 1 to 100
    AbilityType type;
    if (rValue > 56 && rValue <= 97){
        type = AbilityType::DamageDeal;
        createObject(x, y, 40*MyFramework::getWUnit(), 45*MyFramework::getHUnit(), "data/67-Breakout-Tiles.png", basicSpeed, vec2<float>(0,1), type);
    }else if (rValue > 97 && rValue <= 100){
        type = AbilityType::SavingWall;
        createObject(x, y, 40*MyFramework::getWUnit(), 45*MyFramework::getHUnit(), "data/71-Breakout-Tiles.png", basicSpeed, vec2<float>(0,1), type);
    }
}

void AbilityObject::useAbility(){
    if(abType == AbilityType::SavingWall){
        SavingWall::createObject(0, 790*MyFramework::getHUnit(), 1000*MyFramework::getWUnit(), 1000*MyFramework::getHUnit(), "data/72-Breakout-Tiles.png");
    }
    if(abType == AbilityType::DamageDeal){
        DDsCaught++;
    }
}

void AbilityObject::doWhenCollide(){
    useAbility();
    coordinates.x = -100;
    coordinates.y = -100;
    MyFramework::allAbilitiesList.remove(this);
}

