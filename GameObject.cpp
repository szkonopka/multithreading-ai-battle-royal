#include "GameObject.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "helpers/ShapeBuilder.h"

using namespace ShapeBuilder;

void GameObject::draw()
{
    // move object by translating current matrix
    glMatrixMode(GL_VIEWPORT);
    glLoadIdentity();
    glTranslatef(this->xPosition, this->yPosition, 0.0f);
    glColor3fv(basicColor);

    // draw rectangle on given positions
    ShapeBuilder::DrawRectangle2DMiddlePoint(xPosition, yPosition, xSize, ySize);
    glLoadIdentity();
}

void GameObject::moveLeft()
{
    this->xPosition -= this->movement;
    if(this->xPosition < -500)
        this->direction = DIR::RIGHT;
}

void GameObject::moveUp()
{
    this->yPosition += this->movement;
    if(this->yPosition > 500)
        this->direction = DIR::DOWN;
}

void GameObject::moveDown()
{
  this->yPosition -= this->movement;
  if(this->yPosition < -500)
      this->direction = DIR::UP;
}

void GameObject::moveRight()
{
  this->xPosition += this->movement;
  if(this->xPosition > 500)
      this->direction = DIR::LEFT;
}

void GameObject::move()
{
  switch(direction)
  {
      case DIR::RIGHT:
        this->moveRight();
        break;
      case DIR::LEFT:
        this->moveLeft();
        break;
      case DIR::UP:
        this->moveUp();
        break;
      case DIR::DOWN:
        this->moveDown();
        break;
      default:
        this->moveUp();
        break;
  }
}
