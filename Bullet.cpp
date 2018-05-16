#include "Bullet.h"
#include <iostream>

void Bullet::draw()
{
  // move object by translating current matrix
  move();
  glMatrixMode(GL_VIEWPORT);
  glLoadIdentity();
  glTranslatef(this->xPosition, this->yPosition, 0.0f);
  glColor3fv(basicColor);

  // draw rectangle on given positions
  ShapeBuilder::DrawRectangle2DMiddlePoint(xPosition, yPosition, xSize, ySize);
  glLoadIdentity();
}

void Bullet::start()
{
  std::cout << "SHOOOT!" << std::endl;
  move();
}

void Bullet::moveLeft()
{
  this->xPosition -= this->movement;
  if(xPosition < -500.0f)
    delete this;
}

void Bullet::moveRight()
{
  this->xPosition += this->movement;
  if(xPosition > 500.0f)
    delete this;
}

void Bullet::moveUp()
{
  this->yPosition += this->movement;
  if(yPosition > 500.0f)
    delete this;
}

void Bullet::moveDown()
{
  this->yPosition -= this->movement;
  if(yPosition < -500.0f)
    delete this;
}
