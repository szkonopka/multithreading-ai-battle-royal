#include "GameObject.h"
#include "GL/gl.h"
#include "GL/glut.h"

void GameObject::draw() 
{       
    glMatrixMode(GL_VIEWPORT);
    glLoadIdentity();
    glTranslatef(this->xPosition, this->yPosition, 0.0f);
    //glBegin();
    glColor3fv(basicColor);
    glRectf(-50.0f, 50.0f, 50.0f, -50.0f);
    glEnd();
    glLoadIdentity();
}

void GameObject::moveLeft()
{
    this->xPosition -= this->movement;
    if(this->xPosition < -1000)
        this->xPosition = 1000;

    if(this->xPosition > 1000)
        this->xPosition = -1000;
}

void GameObject::moveUp()
{
    this->yPosition += this->movement;
    if(this->yPosition < -1000)
        this->yPosition = 1000;

    if(this->yPosition > 1000)
        this->yPosition = -1000;
}