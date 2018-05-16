#pragma once
#include <iostream>

typedef float color3[3];

enum DIR { RIGHT, LEFT, UP, DOWN };

class GameObject
{
protected:
    float xPosition;
    float yPosition;
    float xSize;
    float ySize;
    float movement;
    color3 basicColor = {1.0f, 0.0f, 0.0f};
    DIR direction;
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
public:
    GameObject() { }
    GameObject(float xPosition, float yPosition, float xSize, float ySize)
    {
      this->xPosition = xPosition;
      this->yPosition = yPosition;
      this->xSize = xSize;
      this->ySize = ySize;
      this->movement = 0.05f;
    }

    GameObject(float xPosition, float yPosition, float xSize, float ySize, int direction)
    : GameObject(xPosition, yPosition, xSize, ySize)
    {
        this->direction = (DIR) direction;
    }

    void setXPosition(float x) { xPosition = x; std::cout << xPosition << std::endl; }
    float getXPosition() { return xPosition; }

    void setYPosition(float y) { yPosition = y; }
    float getYPosition() { return yPosition; }

    void setXSize(float x) { xSize = x; }
    float getXSize() { return xSize; }

    void setYSize(float y) { ySize = y; }
    float getYSize() { return ySize; }

    virtual void draw();
    virtual void move();
};
