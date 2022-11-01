#include "MyFramework.hpp"
#include "deltaTime.hpp"

#include "time.h"
#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;

void MyFramework::PreInit (int& width, int& height, bool& fullscreen){
    width = wWidth;
    height = wHeight;
    fullscreen = false;
}

bool MyFramework::Init(){
    restart = false;
    Object objGenerator;
    BlockObject blockGenerator;
    WallObject wallGenerator;
    initWHUnits1000();
    
    Background = objGenerator.createObject(0, 0, 1000*wUnit, 1000*hUnit, "data/66-Breakout-Tiles.png");
    
    Player = Player->createObject(wUnit*500 - wUnit*45, hUnit*750, wUnit*90, hUnit*10, "data/72-Breakout-Tiles.png", 450, vec2<float>(0,0));
    
    Ball = Ball->createObject(wUnit*500 - wUnit*12, hUnit*725, wUnit*25, hUnit*28, "data/68-Breakout-Tiles.png", 450, vec2<float>(0,0));
    
    wallGenerator.createObject(0, hUnit*900, wUnit*1000, hUnit*100, "data/65-Breakout-Tiles.png");
    wallGenerator.createObject(0, 0, wUnit*1000, hUnit*100, "data/65-Breakout-Tiles.png");
    wallGenerator.createObject(0, 0, wUnit*100, hUnit*1000, "data/65-Breakout-Tiles.png");
    wallGenerator.createObject(wUnit*900, 0, wUnit*100, hUnit*1000, "data/65-Breakout-Tiles.png");
    
    int rows = 5;
    int blocksInARow = 5;
    
    for (int i = 0; i < blocksInARow; ++i) {
        for (int j = 0; j < rows; j++) {
            blockGenerator.createObject(150*wUnit + i*160*wUnit, 100*hUnit + j*100*hUnit, 65*wUnit, 45*hUnit, "data/69-Breakout-Tiles.png", 3, vec2<float>(0,1));
        }
    }
    
    return true;
}

void MyFramework::initWHUnits1000(){
    wUnit = wWidth/1000.0f;
    hUnit = wHeight/1000.0f;
}

void MyFramework::Close(){
}

bool MyFramework::Tick(){
    deltaTime::calculateDTime();
    
    for(const auto& wall : allSavingWalls){
        if((clock() - wall->appeared)/CLOCKS_PER_SEC > wall->lifeTime){
            if(!allSavingWalls.empty()){
                wall->destroyWall();
                break;
            }
        }
    }
    Player->move();
    Ball->move();
    for(const auto& block : allBlocksList){
        block->move();
    }
    for(const auto& ability : allAbilitiesList){
        ability->move();
    }
    
    drawTestBackground();
    drawSprite(Background->getObjSprite(), Background->getX(), Background->getY());
    drawSprite(Player->getObjSprite(), Player->getX(), Player->getY());
    drawSprite(Ball->getObjSprite(), Ball->getX(), Ball->getY());
    for(const auto& ability : allAbilitiesList){
        if(ability->isColliding(Player)){
            ability->doWhenCollide();
            break;
        }
        ability->setMovementSpeed(ability->basicSpeed);
        for(int i = 0; i < allObjectsToCollideVec.size(); ++i){
            auto element = allObjectsToCollideVec[i];
            if(ability->isColliding(element)) {
                if(!allBlocksList.empty()){
                    ability->setMovementSpeed(allBlocksList.back()->getMovementSpeed());
                }
            }
            
        }
        drawSprite(ability->getObjSprite(), ability->getX(), ability->getY());
    }
    for(const auto& wall : allWalls){
        drawSprite(wall->getObjSprite(), wall->getX(), wall->getY());
    }
    
    // wall colliding
    if(Ball->getX() < 100*wUnit || Ball->getX() > 880*wUnit){
        Ball->setMovementDirection(vec2<float>(-Ball->getMovementDirection().x,Ball->getMovementDirection().y));
    }else if(Ball->getY() < 100*hUnit || Ball->getY() > 880*hUnit){
        Ball->setMovementDirection(vec2<float>(Ball->getMovementDirection().x,-Ball->getMovementDirection().y));
    }
    
    // block colliding
    for(int i = 0; i < allObjectsToCollideVec.size(); ++i){
        auto element = allObjectsToCollideVec[i];
        if(Ball->isColliding(element)){
            if(Ball->verticalReflection(element)){
                vec2<float> newDirection = Ball->getMovementDirection();
                newDirection.y = -newDirection.y;
                Ball->setMovementDirection(newDirection);
            }
            else{
                vec2<float> newDirection = Ball->getMovementDirection();
                newDirection.x = - newDirection.x;
                Ball->setMovementDirection(newDirection);
            }
            element->doWhenCollide();
        }
        drawSprite(element->getObjSprite(), element->getX(), element->getY());
    }
    
    //player colliding
    if(Ball->isColliding(Player)){
        if(Ball->verticalReflection(Player)){
            vec2<float> newDirection = Ball->getMovementDirection();
            newDirection.x = -newDirection.x;
            Ball->setMovementDirection(newDirection);
        }
        else{
            vec2<float> newDirection = Ball->getMovementDirection();
            newDirection.y = - newDirection.y;
            Ball->setMovementDirection(newDirection);
        }
    }
    
    // savingwall colliding
    for(const auto& swall : allSavingWalls){
        drawSprite(swall->getObjSprite(), swall->getX(), swall->getY());
        if(Ball->isColliding(swall)){
            vec2<float> newDirection = Ball->getMovementDirection();
            newDirection.y = - newDirection.y;
            Ball->setMovementDirection(newDirection);
            break;
        }
    }
    
    
    
    // end conditions
    // win: blocks destroyed
    if(allBlocksList.size() == 0 && Ball->isColliding(Player)){
        cout << "won" << endl;
        endOfSession();
    }
    // loose: ball is out
    if(Ball->getY() > Player->getY() + 100*hUnit){
        cout << "lost" << endl;
        endOfSession();
    }
    // loose: blocks intersect Player or bottom edge
    for(const auto& block : allBlocksList){
        if(Player->isColliding(block) || block->getY() > wHeight){
            cout << "lost" << endl;
            endOfSession();
            break;
        }
    }
    //loose: took 3 damage from Abilities
    if(AbilityObject::DDsCaught == 3){
        cout << "lost" << endl;
        endOfSession();
    }
    
    return restart;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative){
    cursorX = x - Ball->getX() - (Ball->getWidth()/2);
    cursorY = y - Ball->getY() - (Ball->getHeight()/2);
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased){
    if (button == FRMouseButton::LEFT && cursorToDirectionEnable) {
        vec2<float> ballDirVector(cursorX, cursorY);
        ballDirVector.normalize();
        Ball->setMovementDirection(ballDirVector);
        cursorToDirectionEnable = false;
    }
}

void MyFramework::onKeyPressed(FRKey k){
    switch (k){
        case (FRKey::RIGHT):{
            vec2<float> dirVector(1,0);
            dirVector.normalize();
            Player->setMovementDirection(dirVector);
            if(cursorToDirectionEnable){
                Ball->setMovementDirection(dirVector);
            }
            break;
        }
        case (FRKey::LEFT):{
            vec2<float> dirVector(-1,0);
            dirVector.normalize();
            Player->setMovementDirection(dirVector);
            if(cursorToDirectionEnable){
                Ball->setMovementDirection(dirVector);
            }
            break;
        }
        case (FRKey::UP):{
            endOfSession();
        }
        default:{
            break;
        }
    }
}

void MyFramework::onKeyReleased(FRKey k){
    vec2<float> dirVector(0,0);
    dirVector.normalize();
    Player->setMovementDirection(dirVector);
    if(cursorToDirectionEnable){
        Ball->setMovementDirection(dirVector);
    }
}

const char* MyFramework::GetTitle(){
        return "Arcanoid";
}

void MyFramework::endOfSession(){
    restart = true;
    allObjectsToCollideVec.clear();
    allBlocksList.clear();
    allAbilitiesList.clear();
    AbilityObject::DDsCaught = 0;
}

void MyFramework::setWWidth(int width){
    wWidth = width;
}

void MyFramework::setWHeight(int height){
    wHeight = height;
}

void MyFramework::SetWindowParameters(int width, int height){
    setWWidth(width);
    setWHeight(height);
}

int MyFramework::getWWidth(){
    return wWidth;
}

int MyFramework::getWHeight(){
    return wHeight;
}

float MyFramework::getWUnit(){
    return wUnit;
}

float MyFramework::getHUnit(){
    return hUnit;
}

