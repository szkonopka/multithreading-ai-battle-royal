#include "GL/gl.h"
#include "GL/glut.h"
#include "GameObject.h"
#include "helpers/ShapeBuilder.h"

using namespace ShapeBuilder;

class Bullet : public GameObject
{
public:
  Bullet(float xPosition, float yPosition, float xSize, float ySize, int direction)
  : GameObject(xPosition, yPosition, xSize, ySize, direction)
  {
    this->movement = 1.0f;
  }
  void start();
  virtual void moveLeft();
  virtual void moveRight();
  virtual void moveUp();
  virtual void moveDown();
  virtual void draw();
};
