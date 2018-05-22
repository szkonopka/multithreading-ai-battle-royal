#pragma once
#include "GL/gl.h"
#include "GL/glut.h"
#include "GameObject.h"
#include "Bullet.h"
#include "helpers/ShapeBuilder.h"
#include <vector>

#if defined(__unix__)
# include <unistd.h>
# define SLEEP(x) usleep(x * 1000)
# elif defined (WIN32) || defined(_WIN32)
# include <windows.h>
# define SLEEP(x) Sleep(x)
#endif

using namespace ShapeBuilder;

class Player : public GameObject
{
private:
  bool armored = true;
  std::vector<Bullet> firedBullets;
  std::vector<std::pair<float, float>> waypoints;
  std::vector<bool> visitedWaypoints;
  void initWaypoints();
public:
  Player(float xPosition, float yPosition, float xSize, float ySize, int direction)
  : GameObject(xPosition, yPosition, xSize, ySize, direction)
  { }
  void shoot();
  void takeWeapon();
  void play();
  virtual void draw();
};
