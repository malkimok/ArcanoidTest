#include "MovingObject.hpp"
#include "deltaTime.hpp"

MovingObject::MovingObject(float inputX, float inputY, int inputWidth, int inputHeight, float speed, vec2<float> mDirection){
    coordinates.x = inputX;
    coordinates.y = inputY;
    width = inputWidth;
    height = inputHeight;
    movementSpeed = speed;
    movementDirection = mDirection;
}

vec2<float> MovingObject::getMovementDirection(){
    return movementDirection;
}

void MovingObject::setMovementDirection(vec2<float> dirVector){
    movementDirection = dirVector;
}

void MovingObject::setMovementSpeed(float speed){
    movementSpeed = speed;
}

float MovingObject::getMovementSpeed(){
    return movementSpeed;
}

void MovingObject::move(){
    coordinates.x += movementDirection.x * (deltaTime::getDTime() * movementSpeed);
    coordinates.y += movementDirection.y * (deltaTime::getDTime() * movementSpeed);
}
