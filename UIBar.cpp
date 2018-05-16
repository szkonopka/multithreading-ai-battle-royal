#include "UIBar.h"
#include "helpers/ShapeBuilder.h"

using namespace ShapeBuilder;

void UIBar::drawBackground()
{
  glColor3f(1.0f, 1.0f, 1.0f);
  ShapeBuilder::DrawRectangle2DLeftUpperCorner(xPosition, yPosition, xSize, ySize);
}

void UIBar::drawProgress()
{
  glColor3f(1.0f, 0.0f, 0.0f);
  ShapeBuilder::DrawRectangle2DLeftUpperCorner(xPosition, yPosition, (0.1f * xSize), ySize);
}

void UIBar::draw()
{
  drawBackground();
  drawProgress();
}
