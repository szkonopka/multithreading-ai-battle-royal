#include "ShapeBuilder.h"
#include <math.h>
#define _USE_MATH_DEFINES

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

  void DrawCircle2DMiddlePoint(float x, float y, float width, float height)
  {
    glBegin(GL_POLYGON);
      for(double i = 0; i < 2 * M_PI; i += M_PI / 6)
      {
        glVertex3f(x + cos(i) * width / 2, y + sin(i) * width / 2, 0);
      }
    glEnd();
  }

  void DrawCircle2DUpperCorner(float x, float y, float width, float height)
  {
    glBegin(GL_POLYGON);

    glEnd();
  }
}
