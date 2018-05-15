#include <iostream>

typedef float color3[3];

class GameObject
{
protected:
    float xPosition;
    float yPosition;
    float xSize;
    float ySize;
    float movement;
    color3 basicColor = {1.0f, 0.0f, 0.0f};
public:
    GameObject() { }

    GameObject(float xPosition, float yPosition, float xSize, float ySize) 
    {
        this->xPosition = xPosition;
        this->yPosition = yPosition;
        this->xSize = xSize;
        this->ySize = ySize;
        this->movement = 0.05f;
        //this->basicColor = 
    }

    void setXPosition(float x) { xPosition = x; std::cout << xPosition << std::endl; }
    float getXPosition() { return xPosition; }

    void setYPosition(float y) { yPosition = y; } 
    float getYPosition() { return yPosition; }

    void setXSize(float x) { xSize = x; }
    float getXSize() { return xSize; }

    void setYSize(float y) { ySize = y; }
    float getYSize() { return ySize; }

    void moveLeft();
    void moveUp();
    void draw();
};
