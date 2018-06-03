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
  float destX;
  float destY;
  std::vector<Bullet> *playerBulletsContainer;
public:
  Bullet() { }
  Bullet(float xPosition, float yPosition, float xSize, float ySize, int direction, float _destX, float _destY)
  : GameObject(xPosition, yPosition, xSize, ySize, direction), id(Bullets::BulletID++)
  {
    this->movement = 0.4f;
    destX = _destX;
    destY = _destY;
  }
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
  virtual void draw();
  long getId() { return id; }
  float getDestX() { return destX; }
  float getDestY() { return destY; }
  bool operator==(const Bullet& val) const
  {
    return val.id == id;
  }
};
