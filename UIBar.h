#pragma once
#include "GameObject.h"
#include "Player.h"
#include <vector>

class UIBar : public GameObject
{
private:
  float maxProgress = 1.0f;
  float minProgress = 0.0f;
  float currentProgress = 1.0f;
  void drawBackground(char *teamName, float percentage);
  void drawProgress();
  std::vector<Player *> players;
public:
  void setCurrentProgress(float currentProgress) { this->currentProgress = currentProgress; }
  float getCurrentProgress() { return this->currentProgress; }
  void setPlayers(std::vector<Player *> &_players)
  {
    players = _players;
  }

  UIBar(float xPosition, float yPosition, float xSize, float ySize)
  : GameObject(xPosition, yPosition, xSize, ySize) { }

  virtual void draw(char *teamName, float percentage);
};
