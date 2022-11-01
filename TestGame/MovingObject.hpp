#include "Object.hpp"
#pragma once

class MovingObject: public Object{
private:
    float movementSpeed = 0.0f;
    vec2<float> movementDirection;
public:
    MovingObject() = default;
    MovingObject(float inputX, float inputY, int inputWidth, int inputHeight, float speed, vec2<float> movementDirection);
    void move();
    void setMovementDirection(vec2<float> dirVector);
    vec2<float> getMovementDirection();
    float getMovementSpeed();
    void setMovementSpeed(float speed);
};
