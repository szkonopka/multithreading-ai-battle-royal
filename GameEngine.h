#pragma once
#include <vector>
#include "Player.h"
#include "UIBar.h"
#include <thread>
#include <algorithm>

typedef float color3[3];

using namespace Players;

class GameEngine
{
private:
  int membersInTeam;
  int teamSize = 3;
  std::vector<Player *> teamA;
  std::vector<Player *> teamB;
  std::vector<Bullet> teamABullets;
  std::vector<Bullet> teamBBullets;
  Player *go;
  Player *go2;
  UIBar *teamABar;
  UIBar *teamBBar;
  float teamASumHP = 0, teamBSumHP = 0, teamATotalHP = 0, teamBTotalHP = 0;
  float matrixWidth;
public:
  GameEngine(float _matrixWidth)
  {
    matrixWidth = _matrixWidth;
    teamABar = new UIBar(-matrixWidth, matrixWidth - 20.0f, matrixWidth / 2, 30.0f);
    teamBBar = new UIBar(matrixWidth / 2, matrixWidth- 20.0f, matrixWidth / 2, 30.0f);
  }
  void CheckForCollisions();
  void CheckBulletsCollision();
  void CheckInWeaponsRange();
  static void ShootTickRate();
  void Refresh();
  void Redraw();
  void Run();
};
