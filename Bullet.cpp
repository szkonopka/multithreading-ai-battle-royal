#include "Bullet.h"
#include <iostream>

void Bullet::draw()
{
  // move object by translating current matrix

  if(xPosition < destX)
  {
    this->direction = (DIR) 0;
  }

  if(xPosition > destX)
  {
    this->direction = (DIR) 1;
  }
  this->move();

  if(yPosition < destY)
  {
    this->direction = (DIR) 2;
  }

  if(yPosition > destY)
  {
    this->direction = (DIR) 3;
  }
  this->move();

  glMatrixMode(GL_VIEWPORT);
  glLoadIdentity();
  glTranslatef(this->xPosition, this->yPosition, 0.0f);
  glColor3fv(basicColor);
  glColor3f(0.0f, 0.0f, 0.0f);
  // draw rectangle on given positions
  //ShapeBuilder::DrawRectangle2DMiddlePoint(xPosition, yPosition, xSize, ySize);
  ShapeBuilder::DrawCircle2DMiddlePoint(xPosition, yPosition, 20.0f, 20.0f);
  glLoadIdentity();
}

void Bullet::start(std::vector<Bullet> &bullets, float bulletX, float bulletY, float xdest, float ydest)
{

}

void Bullet::moveLeft()
{
  this->xPosition -= this->movement;
}

void Bullet::moveRight()
{
  this->xPosition += this->movement;
}

void Bullet::moveUp()
{
  this->yPosition += this->movement;
}

void Bullet::moveDown()
{
  this->yPosition -= this->movement;
}
