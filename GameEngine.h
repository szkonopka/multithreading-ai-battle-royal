#pragma once
#include <vector>
#include "Player.h"
#include "UIBar.h"
#include <thread>

class GameEngine
{
private:
  int membersInTeam;
  int teamSize = 3;
  std::vector<Player> teamA;
  std::vector<Player> teamB;
  std::vector<Bullet> teamABullets;
  std::vector<Bullet> teamBBullets;
  Player *go;
  Player *go2;
  UIBar *teamABar;
  UIBar *teamBBar;
public:
  GameEngine(float matrixWidth)
  {
    //teamABar = new UIBar(-matrixWidth, matrixWidth - 20.0f, matrixWidth / 2, 30.0f);
    teamBBar = new UIBar(matrixWidth / 2, matrixWidth - 20.0f, matrixWidth / 2, 30.0f);
    go = new Player(0.0f, 0.0f, 100, 100, 0);
    go2 = new Player(0.0f, 0.0f, 100, 100, 1);

  }
  void CheckForCollisions();
  void Refresh();
  void Redraw();
  void Run();
};
