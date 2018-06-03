#pragma once
#include "GL/gl.h"
#include "GL/glut.h"
#include "GameObject.h"
#include "Bullet.h"
#include "helpers/ShapeBuilder.h"
#include <vector>
#include <random>
#include "Weapon.h"
#include <mutex>
#include "helpers/Game.h"
#include "Armory.h"

#if defined(__unix__)
# include <unistd.h>
# define SLEEP(x) usleep(x * 1000)
# elif defined (WIN32) || defined(_WIN32)
# include <windows.h>
# define SLEEP(x) Sleep(x)
#endif

using namespace ShapeBuilder;
using namespace GameState;

class Player : public GameObject
{
private:
  bool isAlive = true;
  int id;
  bool armored = true;
  std::vector<std::pair<float, float>> waypoints;
  std::vector<bool> visitedWaypoints;
  float range = 100.0f;
  const float maxHp = 100.0f;
  float hp;
  float *rangeColor;
  Weapon *currentWeapon = nullptr;
  Armory *teamArmory = nullptr;
  void initWaypoints();
  int currentWeaponBullets = 0;
  int shootingRound = 0;
  std::mutex *thisWeaponResource = nullptr;
  Weapon *noWeapon;
  int currentWeaponId;
public:
  std::vector<Bullet> firedBullets;
  Player(float xPosition, float yPosition, float xSize, float ySize, int direction, float color3[], Armory *&_teamArmory)
  : GameObject(xPosition, yPosition, xSize, ySize, direction), hp(maxHp), id(Players::PlayerID++), teamArmory(_teamArmory)
  {
    basicColor[0] = color3[0];
    basicColor[1] = color3[1];
    basicColor[2] = color3[2];
    rangeColor = new float[4];
    rangeColor[0] = color3[0];
    rangeColor[1] = color3[1];
    rangeColor[2] = color3[2];
    rangeColor[3] = 0.1;
    noWeapon = new Weapon();
  }

  void setWeapon(Weapon *_weapon)
  {
    currentWeapon = _weapon;
    currentWeapon->setOwnerID(id);
  }
  void setHp(int _hp) { hp = _hp < 0 ? 0 : _hp; }
  float getHp() { return hp; }
  void setIsAlive(bool _isAlive) { isAlive = _isAlive; }
  bool getIsAlive() { return isAlive; }
  int getId() { return id; }
  float getMaxHp() { return maxHp; }
  float getRange()
  {
    if(currentWeapon != nullptr)
      return (currentWeapon->getRange() + xSize) / 4;

    return xSize / 2;
  }
  virtual float getXSize() { return xSize / 4; }
  virtual float getYSize() { return ySize / 4; }
  Weapon *&getCurrentWeapon() { return currentWeapon; }
  void Shoot(std::mutex &bulletResource, std::mutex &weaponResource, float x, float y);
  void Play(std::mutex *weaponResource);
  void InitWeapon(int id);
  void Destroy();
  virtual void draw();
  bool operator==(const Player &val) const
  {
    return val.id == id;
  }
};
