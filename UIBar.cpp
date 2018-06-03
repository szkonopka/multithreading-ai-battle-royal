#include "UIBar.h"
#include "helpers/ShapeBuilder.h"
#include <string>

using namespace ShapeBuilder;

void UIBar::drawBackground(char *teamName, float percentage)
{
  glColor3f(0.2f, 0.2f, 0.3f);
  glRasterPos3f(xPosition, yPosition - 2.5 * ySize, 0);
  int i = 0;
  while(teamName[i] != '\0')
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, teamName[i]);
    i++;
  }

  percentage *= 100;
  std::string percentageTxt = std::to_string(percentage);
  i = 0;
  int limit = percentage >= 100.0f ? 3 : (percentage > 10.0f ? 2 : 1);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '[');
  while(i != limit)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, percentageTxt[i]);
    i++;
  }
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '%');
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ']');

  glColor3f(0.65f, 0.3f, 0.25f);
  ShapeBuilder::DrawRectangle2DLeftUpperCorner(xPosition, yPosition - 4 * ySize, xSize, ySize);

  glRasterPos3f(xPosition, yPosition - (7) * ySize, 0);
  i = 0;
  std::string playerId;
  std::string weaponName;
  int j = 0, k = 0;
  for(Player *player : players)
  {
    glRasterPos3f(xPosition, yPosition - (7 + j * 2) * ySize, 0);
    playerId = std::to_string(player->getId());
    weaponName = player->getCurrentWeapon()->getName();
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, playerId[0]);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '-');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ' ');
    while(k < weaponName.size())
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, weaponName[k]);
      k++;
    }
    k = 0;
    j++;
  }
}

void UIBar::drawProgress()
{
  if(currentProgress < 0)
  {
    currentProgress = 0;
  }

  glColor3f(0.9f, 0.1f, 0.25f);
  ShapeBuilder::DrawRectangle2DLeftUpperCorner(xPosition, yPosition - 4 * ySize, (currentProgress * xSize), ySize);
}

void UIBar::draw(char *teamName, float percentage)
{
  drawBackground(teamName, percentage);
  drawProgress();
}
