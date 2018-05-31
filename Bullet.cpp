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
  glColor3f(0.0f, 0.0f, 0.0f);
  // draw rectangle on given positions
  //ShapeBuilder::DrawRectangle2DMiddlePoint(xPosition, yPosition, xSize, ySize);
  ShapeBuilder::DrawCircle2DMiddlePoint(xPosition, yPosition, 20.0f, 20.0f);
  glLoadIdentity();
}

void Bullet::start(std::vector<Bullet> &bullets)
{
  //std::cout << "SHOOOT!" << std::endl;
  playerBulletsContainer = &bullets;
  move();
}

void Bullet::moveLeft()
{
  this->xPosition -= this->movement;
  if(xPosition < -500.0f)
  {}
    //delete this;
}

void Bullet::moveRight()
{
  this->xPosition += this->movement;
  if(xPosition > 500.0f)
  {}
    //delete this;
}

void Bullet::moveUp()
{
  this->yPosition += this->movement;
  if(yPosition > 500.0f)
  {}
    //delete this;
}

void Bullet::moveDown()
{
  this->yPosition -= this->movement;
  if(yPosition < -500.0f)
  {}
    //delete this;
}
