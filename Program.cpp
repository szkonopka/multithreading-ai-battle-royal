#include "stdio.h"
#include "stdlib.h"
#include "GameObject.h"
#include "Player.h"
#include "UIBar.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include <thread>
#include <iostream>

bool firstShoot = false;
color3 goColor = {1.0f, 0.0f, 0.0f};
Player *go = new Player(0.0f, 0.0f, 100, 100, 0);
Player *go2 = new Player(0.0f, 0.0f, 100, 100, 1);
UIBar *teamABar = new UIBar(-1000.0f, 980.0f, 500.0f, 30.0f);
UIBar *teamBBar = new UIBar(500.0f, 980.0f, 500.0f, 30.0f);

void resizeScreen(GLsizei horizontal, GLsizei vertical)
{
    GLfloat aspectRatio;
    if(vertical == 0)
        vertical = 1;

    glViewport(0, 0, horizontal, vertical);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    if(horizontal <= vertical)
        glOrtho(-1000.0, 1000.0, -1000.0/aspectRatio, 1000.0/aspectRatio, 1.0, -1.0);
    else
        glOrtho(-1000.0*aspectRatio, 1000.0*aspectRatio, -1000.0, 1000.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myInit(void)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    go->draw();
    go2->draw();
    teamABar->draw();
    teamBBar->draw();

    glFlush();
}

void requestAnimationFrame()
{
  if(!firstShoot)
  {
      go->shoot();
      go2->shoot();
      firstShoot = true;
  }
  go->move();
  go2->move();
  glutPostRedisplay();
}

void openGLThread(int argc, char *argv[])
{
  glutInit(&argc, argv); // initialize the glut library, allow GLUT to create a seesion with window system
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // set display mode to single display buffor and RGB color mode
  glutInitWindowSize(800, 800);
  glutCreateWindow("Battle royal"); // create application window with "Battle royal" in label
  glutIdleFunc(requestAnimationFrame);
  glutDisplayFunc(renderScene); // set core displaying function
  glutReshapeFunc(resizeScreen); // set core window resizing function
  myInit(); // this function will be invoke before rendering, it clears window
  glutMainLoop(); // run main GLUT library core}
}

int main(int argc, char *argv[])
{
  std::thread mainGL(&openGLThread, argc, argv);
  mainGL.join();
  return 0;
}
