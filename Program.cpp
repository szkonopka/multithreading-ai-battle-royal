#include "stdio.h"
#include "stdlib.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include <thread>
#include <iostream>
#include "GameEngine.h"
#include "helpers/Game.h"
#include <chrono>

using namespace GameState;

GameEngine ge(GameState::MatrixWidth);

void checkKeyboardKey(unsigned char key, int x, int y)
{
  if(key == 27)
  {
    *GameState::GameOnPtr = false;
    exit(0);
  }
}

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
        glOrtho(-GameState::MatrixWidth, GameState::MatrixWidth, -GameState::MatrixWidth/aspectRatio, GameState::MatrixWidth/aspectRatio, 1.0, -1.0);
    else
        glOrtho(-GameState::MatrixWidth*aspectRatio, GameState::MatrixWidth*aspectRatio, -GameState::MatrixWidth, GameState::MatrixWidth, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myInit(void)
{
    glClearColor(0.9f, 0.9f, 0.9f, 0.7f);
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
  GameState::WindowID = glutCreateWindow("Deathmatch simulation"); // create application window with "Battle royal" in label
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glutIdleFunc(requestAnimationFrame);
  glutKeyboardFunc(checkKeyboardKey);
  glutDisplayFunc(renderScene); // set core displaying function
  glutReshapeFunc(resizeScreen); // set core window resizing function
  myInit(); // this function will be invoke before rendering, it clears window
  glutMainLoop(); // run main GLUT library core}
}

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    std::cout << "Not enough arguments." << std::endl;
    return 0;
  }

  std::thread mainGL(&openGLThread, argc, argv);

  char *arg = argv[1];
  int teamSize;
  sscanf(argv[1], "%d", &teamSize);

  std::thread gameEngine(&GameEngine::Run, &ge, teamSize);
  gameEngine.join();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  //mainGL.detach();
  glutDestroyWindow(GameState::WindowID);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  mainGL.join();
  return 0;
}
