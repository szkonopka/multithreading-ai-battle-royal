#include "Player.h"
#include <iostream>
#include <thread>
#include <cstdlib>

void Player::draw()
{
  if(isAlive && *GameState::GameOnPtr)
  {
    // move object by translating current matrix
    glMatrixMode(GL_VIEWPORT);
    glLoadIdentity();
    glTranslatef(this->xPosition, this->yPosition, 0.0f);



    if(currentWeapon->getArmored())
    {
      glColor4fv(rangeColor);
      ShapeBuilder::DrawCircle2DMiddlePoint(xPosition, yPosition, xSize + currentWeapon->getRange(), ySize + currentWeapon->getRange());
    }

    // draw rectangle on given positions
    glColor3fv(basicColor);
    ShapeBuilder::DrawCircle2DMiddlePoint(xPosition, yPosition, xSize, ySize);

    for(Bullet &bullet : firedBullets)
    {
      try
      {
        bullet.draw();
      }
      catch(std::exception e)
      {
        Bullet *pointer = &bullet;
        delete pointer;
      }
    }

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
    waypoints.push_back(std::make_pair(randomValue(gen) * GameState::MatrixWidth - GameState::MatrixWidth / 2, randomValue(gen) * GameState::MatrixWidth - GameState::MatrixWidth / 2));
    visitedWaypoints.push_back(0);
  }
}

void Player::shoot(std::mutex &bulletResource, std::mutex &weaponResource, float destx, float desty)
{
  teamArmory->getResources()[currentWeapon->getId()]->lock();
  weaponResource.lock();
  if(currentWeaponBullets > currentWeapon->getCapacity())
  {
    teamArmory->getResources()[(currentWeapon->getId() + 1) % 3]->lock();
    currentWeapon = teamArmory->getWeapons()[(currentWeapon->getId() + 1) % 3];
    teamArmory->getResources()[(currentWeapon->getId() + 1) % 3]->unlock();
    //shootingRound++;
    currentWeaponBullets = 0;

  }

  if(currentWeapon->getArmored())
  {
    bulletResource.lock();
    Bullet *bullet = new Bullet(xPosition, yPosition, 80, 30, direction, destx, desty);
    firedBullets.push_back(*bullet);
    currentWeaponBullets++;
    bulletResource.unlock();
  }
  weaponResource.unlock();
  teamArmory->getResources()[currentWeapon->getId()]->unlock();
}


void Player::play()
{
  while(true)
  {
    if(!isAlive || !*GameState::GameOnPtr)
      break;
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
        currentWaypoint++;
      }
      SLEEP(5);
    }
  }
}
