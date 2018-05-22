#include "Player.h"
#include <iostream>
#include <thread>
#include <cstdlib>

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

void Player::initWaypoints()
{
  srand( time( NULL ) );
  waypoints.clear();
  visitedWaypoints.clear();
  int waypointsAmount = std::rand() % 5 + 5;
  for(int i = 0; i < waypointsAmount; i++)
  {
    waypoints.push_back(std::make_pair(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000));
    visitedWaypoints.push_back(0);
  }
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

void Player::play()
{

  while(true)
  {
    initWaypoints();
    int currentWaypoint = 0;
    //waypoints[currentWaypoint] = std::make_pair(-1000, -1000);
    while(currentWaypoint < waypoints.size()) {
      //this->direction = (DIR) 0;
      //std::cout << waypoints[currentWaypoint].first << " : " << waypoints[currentWaypoint].second << std::endl;
      if(waypoints[currentWaypoint].first < this->xPosition)
      {
        this->direction = (DIR) 0;
      }

      if(waypoints[currentWaypoint].first > this->xPosition)
      {
        this->direction = (DIR) 1;
      }

      this->move();

      if(waypoints[currentWaypoint].second < this->yPosition)
      {
        this->direction = (DIR) 2;
      }

      if(waypoints[currentWaypoint].second > this->yPosition)
      {
        this->direction = (DIR) 3;
      }

      this->move();
      currentWaypoint++;

      if((waypoints[currentWaypoint].first - this->xSize < this->xPosition < waypoints[currentWaypoint].first + this->xSize)
      && (waypoints[currentWaypoint].second - this->xSize < this->yPosition < waypoints[currentWaypoint].second + this->xSize))
      {
        std::cout << "NOWY WAYPOINT" << std::endl;
        currentWaypoint++;
      }
      SLEEP(1);
    }
  }

}

void Player::takeWeapon()
{

}
