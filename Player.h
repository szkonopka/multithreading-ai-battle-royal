#include "GameObject.h"

class Player : public GameObject
{
private:

public:
    Player(int xPosition, int yPosition, int xSize, int ySize, int basicColor)
    : GameObject(xPosition, yPosition, xSize, ySize, basicColor) { }
    void move();
    void shoot();
    void takeWeapon();
}