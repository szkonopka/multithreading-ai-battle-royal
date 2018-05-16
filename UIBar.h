#pragma once
#include "GameObject.h"

class UIBar : public GameObject
{
private:
  float maxProgress = 1.0f;
  float minProgress = 0.0f;
  float currentProgress = 0.6f;
  void drawBackground();
  void drawProgress();
public:
  void setCurrentProgress(float currentProgress) { this->currentProgress = currentProgress; }
  float getCurrentProgress() { return this->currentProgress; }
  UIBar(float xPosition, float yPosition, float xSize, float ySize)
  : GameObject(xPosition, yPosition, xSize, ySize) { }
  virtual void draw();
};
