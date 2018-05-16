#include "GL/gl.h"
#include "GL/glut.h"
#include "GameObject.h"
#include "Bullet.h"
#include "helpers/ShapeBuilder.h"
#include <vector>

using namespace ShapeBuilder;

class Player : public GameObject
{
private:
  bool armored = true;
  std::vector<Bullet> firedBullets;
public:
  Player(float xPosition, float yPosition, float xSize, float ySize, int direction)
  : GameObject(xPosition, yPosition, xSize, ySize, direction)
  { }
  void shoot();
  void takeWeapon();
  virtual void draw();
};
