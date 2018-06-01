#pragma once
#include <vector>
#include "Player.h"
#include "UIBar.h"
#include <thread>
#include <algorithm>
#include <mutex>
#include "Armory.h"
#include "helpers/Game.h"
typedef float color3[3];

using namespace Players;
using namespace GameState;

struct GameResources
{
  std::mutex playerResource;
  std::mutex bulletResource;
  std::mutex weaponResource;
};

class GameEngine
{
private:
  int membersInTeam;
  int teamSize = 3;
  std::vector<Player *> teamA;
  std::vector<Player *> teamB;
  std::vector<Bullet> teamABullets;
  std::vector<Bullet> teamBBullets;
  UIBar *teamABar;
  UIBar *teamBBar;
  GameResources gr;
  float teamASumHP = 0, teamBSumHP = 0, teamATotalHP = 0, teamBTotalHP = 0;
  float matrixWidth;
  bool gameOn = true;
public:
  GameEngine(float _matrixWidth) : gameOn(true)
  {
    matrixWidth = _matrixWidth;
    teamABar = new UIBar(-matrixWidth + 40.0f, matrixWidth - 20.0f, matrixWidth / 2, 30.0f);
    teamBBar = new UIBar(matrixWidth / 2 - 40.0f, matrixWidth- 20.0f, matrixWidth / 2, 30.0f);
  }
  void CheckForCollisions();
  void CheckBulletsCollision();
  void CheckInWeaponsRange();
  void ShootInWeaponsRange(float ax, float bx, float ay, float by, Player *&shooter);
  void CheckTeamCollision(std::vector<Player *> &firstTeam, std::vector<Player *> &secondTeam);
  void ShootTickRate();
  void Refresh();
  void Redraw();
  void Run();
};
