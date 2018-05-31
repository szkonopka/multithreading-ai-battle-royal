#pragma once
#include "GL/gl.h"
#include "GL/glut.h"
#include "GameObject.h"
#include "helpers/ShapeBuilder.h"
#include <vector>

using namespace ShapeBuilder;

namespace Bullets {
  static long BulletID = 0;
}

class Bullet : public GameObject
{
private:
  long id;
  std::vector<Bullet> *playerBulletsContainer;
public:
  Bullet(float xPosition, float yPosition, float xSize, float ySize, int direction)
  : GameObject(xPosition, yPosition, xSize, ySize, direction), id(Bullets::BulletID++)
  {
    this->movement = 1.0f;
  }
  void start(std::vector<Bullet> &bullets);
  virtual void moveLeft();
  virtual void moveRight();
  virtual void moveUp();
  virtual void moveDown();
  virtual void draw();
  long getId() { return id; }

  bool operator==(const Bullet& val) const
  {
    return val.id == id;
  }
};
