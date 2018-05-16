#include "Player.h"

void Player::draw()
{
  // move object by translating current matrix
  glMatrixMode(GL_VIEWPORT);
  glLoadIdentity();
  glTranslatef(this->xPosition, this->yPosition, 0.0f);
  glColor3fv(basicColor);

  for(int i = 0; i < firedBullets.size(); i++)
  {
    try
    {
      firedBullets[i].draw();
    }
    catch(std::exception e)
    {
      Bullet *pointer = &firedBullets[i];
      delete pointer;
      firedBullets.erase(firedBullets.begin() + i);
    }

  }

  // draw rectangle on given positions
  ShapeBuilder::DrawRectangle2DMiddlePoint(xPosition, yPosition, xSize, ySize);
  glLoadIdentity();
}

void Player::shoot()
{
  if(armored)
  {
    Bullet *bullet = new Bullet(xPosition, yPosition, 80, 30, direction);
    firedBullets.push_back(*bullet);
    bullet->start();
  }
}

void Player::takeWeapon()
{

}
