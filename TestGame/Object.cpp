#include "MyFramework.hpp"
#include "Object.hpp"
#include "deltaTime.hpp"
#include <cmath>

void Object::doWhenCollide(){
}

Object::Object(float inputX, float inputY, int inputWidth, int inputHeight){
    coordinates.x = inputX;
    coordinates.y = inputY;
    width = inputWidth;
    height = inputHeight;
}

Object* Object::createObject(float x, float y, int width, int height, const char* path){
    Object* obj = new Object(x, y, width, height);
    obj->attachSprite(path);
    return obj;
}

void Object::attachSprite(const char* path){
    objSprite = createSprite(path);
    setSpriteSize(objSprite, width, height);
}

bool Object::isColliding(Object* potentiallyCollidingObj){
    return(this->coordinates.x + eps < potentiallyCollidingObj->coordinates.x + potentiallyCollidingObj->width &&
            this->coordinates.x + this->width > potentiallyCollidingObj->coordinates.x + eps &&
            this->coordinates.y + eps < potentiallyCollidingObj->coordinates.y + potentiallyCollidingObj->height &&
           this->height + this->coordinates.y > potentiallyCollidingObj->coordinates.y + eps);
}

bool Object::verticalReflection(Object* collidingObj){
    float thisMinY = this->coordinates.y - this->height;
    float thisMaxY= this->coordinates.y;
    float collidingObjMinY = collidingObj->coordinates.y - collidingObj->height;
    float collidingObjMaxY = collidingObj->coordinates.y;
    
    return(thisMinY >= collidingObjMaxY ||
           thisMaxY <= collidingObjMinY);
}

Sprite* Object::getObjSprite(){
    return objSprite;
}

float Object::getX(){
    return coordinates.x;
}

float Object::getY(){
    return coordinates.y;
}

int Object::getWidth(){
    return width;
}

int Object::getHeight(){
    return height;
}

