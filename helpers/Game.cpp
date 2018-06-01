#include "Game.h"

namespace Players
{
  int PlayerID = 0;
  bool IsShooting = false;
  char *TeamAName = "TEAM A ";
  char *TeamBName = "TEAM B ";
};

namespace GameState
{
  bool *GameOnPtr = new bool(true);
  float MatrixWidth = 1500.0f;
  int WindowID;
};
