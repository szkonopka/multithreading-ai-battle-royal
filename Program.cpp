#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include <thread>
#include <iostream>
#include "GameEngine.h"

float matrixWidth = 1500.0f;
GameEngine ge(matrixWidth);

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
        glOrtho(-matrixWidth, matrixWidth, -matrixWidth/aspectRatio, matrixWidth/aspectRatio, 1.0, -1.0);
    else
        glOrtho(-matrixWidth*aspectRatio, matrixWidth*aspectRatio, -matrixWidth, matrixWidth, 1.0, -1.0);

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
    ge.Redraw();
    glFlush();
}

void requestAnimationFrame()
{
  ge.Refresh();
  glutPostRedisplay();
}

void openGLThread(int argc, char *argv[])
{
  glutInit(&argc, argv); // initialize the glut library, allow GLUT to create a seesion with window system
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // set display mode to single display buffor and RGB color mode
  glutInitWindowSize(600, 600);
  glutCreateWindow("Battle royal"); // create application window with "Battle royal" in label
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glutIdleFunc(requestAnimationFrame);
  glutDisplayFunc(renderScene); // set core displaying function
  glutReshapeFunc(resizeScreen); // set core window resizing function
  myInit(); // this function will be invoke before rendering, it clears window
  glutMainLoop(); // run main GLUT library core}
}

int main(int argc, char *argv[])
{
  std::thread mainGL(&openGLThread, argc, argv);
  ge.Run();
  mainGL.join();

  return 0;
}
