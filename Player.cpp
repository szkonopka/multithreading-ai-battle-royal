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

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(xPosition - xSize / 5, yPosition - ySize / 5, 0);
    std::string number = std::to_string(id);
    int i = 0;
    while(number[i] != '\0')
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, number[i]);
      i++;
    }

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

void Player::InitWeapon(int id)
{
  if(!currentWeapon->getArmored())
  {
    teamArmory->getResources()[id]->lock();
    teamArmory->setWeaponState(id, true);
    currentWeapon = teamArmory->getWeapons()[id];
    currentWeaponId = id;
  }
}

void Player::Shoot(std::mutex &bulletResource, std::mutex &weaponResource, float destx, float desty)
{
  weaponResource.lock();
  if(currentWeapon->getArmored())
  {
    if(currentWeaponBullets < currentWeapon->getCapacity())
    {
      currentWeaponBullets++;
      std::cout << id << " wystrzelil: " << currentWeaponBullets << std::endl;
      bulletResource.lock();
      Bullet *bullet = new Bullet(xPosition, yPosition, 80, 30, direction, destx, desty);
      firedBullets.push_back(*bullet);
      bulletResource.unlock();
    }
  }
  weaponResource.unlock();
}


void Player::Play(std::mutex *weaponResource)
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

      if(weaponResource->try_lock())
      {
        if(currentWeaponBullets >= currentWeapon->getCapacity() && currentWeapon->getArmored())
        {
          teamArmory->setWeaponState(currentWeaponId, false);
          teamArmory->getResources()[currentWeaponId]->unlock();
          currentWeapon = noWeapon;
          currentWeaponBullets = 0;
        }
      }

      if(currentWeapon->getArmored() == false)
      {
        //teamArmory->getResources()[currentWeaponId]->unlock();
        if(teamArmory->getResources()[(currentWeaponId + 1) % 3]->try_lock())
        {
          std::cout << id << " zmiana broni!" << std::endl;
          teamArmory->setWeaponState(((currentWeaponId + 1) % 3), true);
          currentWeapon = teamArmory->getWeapons()[(currentWeaponId + 1) % 3];
          currentWeaponId = currentWeapon->getId();
        }
        else if(teamArmory->getResources()[(currentWeaponId + 2) % 3]->try_lock())
        {
          std::cout << id << " zmiana broni!" << std::endl;
          teamArmory->setWeaponState(((currentWeaponId + 2) % 3), true);
          currentWeapon = teamArmory->getWeapons()[(currentWeaponId + 2) % 3];
          currentWeaponId = currentWeapon->getId();
        }
        /*
        if(teamArmory->getWeaponState((currentWeaponId + 1) % 3) == false)
        {
          std::cout << id << " zmiana broni!" << std::endl;
          teamArmory->setWeaponState(((currentWeaponId + 1) % 3), true);
          currentWeapon = teamArmory->getWeapons()[(currentWeaponId + 1) % 3];
          currentWeaponId = currentWeapon->getId();
        }
        */
      }

      weaponResource->unlock();
    }
  }
}

void Player::Destroy()
{
  teamArmory->setWeaponState(currentWeaponId, false);
  teamArmory->getResources()[currentWeaponId]->unlock();
  isAlive = false;
}
