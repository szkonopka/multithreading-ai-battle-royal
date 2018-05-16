#include "ShapeBuilder.h"

namespace ShapeBuilder
{
  void DrawRectangle2DMiddlePoint(float x, float y, float width, float height)
  {
    glBegin(GL_POLYGON);
      glVertex3f(x - (width / 2), y + (height / 2), 0);
      glVertex3f(x + (width / 2), y + (height / 2), 0);
      glVertex3f(x + (width / 2), y - (height / 2), 0);
      glVertex3f(x - (width / 2), y - (height / 2), 0);
    glEnd();
  }

  void DrawRectangle2DLeftUpperCorner(float x, float y, float width, float height)
  {
    glBegin(GL_POLYGON);
      glVertex3f(x, y, 0);
      glVertex3f(x + width, y, 0);
      glVertex3f(x + width, y - height, 0);
      glVertex3f(x, y - height, 0);
    glEnd();
  }

  void DrawCircle2D()
  {

  }
}
