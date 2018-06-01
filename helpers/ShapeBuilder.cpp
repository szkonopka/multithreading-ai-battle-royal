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
    float theta = 2.0f * M_PI / float(60);
    float tangential_factor = tanf(theta);
    float radial_factor = cosf(theta);
    float cx = width / 2;
    float cy = 0;

    glBegin(GL_POLYGON);
    for(int ii = 0; ii < 60; ii++)
    {
      glVertex3f(x + cx, y + cy, 0);

      float tx = -cy;
      float ty = cx;

      cx += tx * tangential_factor;
      cy += ty * tangential_factor;

      cx *= radial_factor;
      cy *= radial_factor;
    }
    glEnd();
  }

  void DrawCircle2DUpperCorner(float x, float y, float width, float height)
  {
    glBegin(GL_POLYGON);

    glEnd();
  }
}
