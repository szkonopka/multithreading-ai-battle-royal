#include "Player.h"
#include <iostream>
#include <thread>
#include <cstdlib>

void Player::draw()
{
  if(isAlive)
  {
    // move object by translating current matrix
    glMatrixMode(GL_VIEWPORT);
    glLoadIdentity();
    glTranslatef(this->xPosition, this->yPosition, 0.0f);

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

    if(currentWeapon != nullptr)
    {
      glColor4fv(rangeColor);
      ShapeBuilder::DrawCircle2DMiddlePoint(xPosition, yPosition, xSize + currentWeapon->getRange(), ySize + currentWeapon->getRange());
    }

    // draw rectangle on given positions
    //ShapeBuilder::DrawRectangle2DMiddlePoint(xPosition, yPosition, xSize, ySize);
    glColor3fv(basicColor);
    ShapeBuilder::DrawCircle2DMiddlePoint(xPosition, yPosition, xSize, ySize);

    glLoadIdentity();
  }
}

void Player::initWaypoints()
{
  thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<> randomValue(0.0, 1.0);

  waypoints.clear();
  visitedWaypoints.clear();
  int waypointsAmount = std::rand() % 5 + 5;
  for(int i = 0; i < waypointsAmount; i++)
  {
    //waypoints.push_back(std::make_pair(std::rand() % 500 - 500, std::rand() % 500 - 500));
    waypoints.push_back(std::make_pair(randomValue(gen) * 1000 - 500, randomValue(gen) * 1000 - 500));
    visitedWaypoints.push_back(0);
  }
}

void Player::shoot()
{
  if(currentWeapon != nullptr)
  {
    Bullet *bullet = new Bullet(xPosition, yPosition, 80, 30, direction);
    firedBullets.push_back(*bullet);
    bullet->start(*&firedBullets);
  }
}


void Player::play()
{

  while(true)
  {
    initWaypoints();
    int currentWaypoint = 0;
    while(currentWaypoint < waypoints.size()) {
      if(waypoints[currentWaypoint].first > this->xPosition)
      {
        this->direction = (DIR) 0;
      }

      if(waypoints[currentWaypoint].first < this->xPosition)
      {
        this->direction = (DIR) 1;
      }
      this->move();

      if(waypoints[currentWaypoint].second > this->yPosition)
      {
        this->direction = (DIR) 2;
      }

      if(waypoints[currentWaypoint].second < this->yPosition)
      {
        this->direction = (DIR) 3;
      }
      this->move();

      if(((waypoints[currentWaypoint].first - this->xSize) <= this->xPosition
      && (waypoints[currentWaypoint].first + this->xSize) >= this->xPosition)
      || ((waypoints[currentWaypoint].second - this->xSize) <= this->yPosition
      && (waypoints[currentWaypoint].second + this->xSize) >= this->yPosition))
      {
        //std::cout << "NOWY WAYPOINT" << std::endl;
        currentWaypoint++;
      }
      //std::cout << "(" << this->xPosition << "," << this->yPosition << ") heading to (" << waypoints[currentWaypoint].first << "," << waypoints[currentWaypoint].second << ")"<< std::endl;
      //std::cout << "X: " << (waypoints[currentWaypoint].first - this->xSize) << " <= " << this->xPosition << " <= " << (waypoints[currentWaypoint].first + this->xSize) << std::endl;
      //std::cout << "Y: " << (waypoints[currentWaypoint].second - this->xSize) << " <= " << this->yPosition << " <= " << (waypoints[currentWaypoint].second + this->xSize) << std::endl;
      SLEEP(1);
    }
  }

}

void Player::takeWeapon()
{

}
