#include "GameObject.h"

class Player : public GameObject
{
private:

public:
    Player(float xPosition, float yPosition, float xSize, float ySize, int direction)
    : GameObject(xPosition, yPosition, xSize, ySize, direction) { }
    void shoot();
    void takeWeapon();
};
