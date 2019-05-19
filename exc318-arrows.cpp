// 
// Cycle through fonts using arrow keys
//
//
//

#include <cstdlib>
#include <cmath>
#include <iostream>

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#endif

using namespace std;

static void *fonts[] = {
  GLUT_BITMAP_8_BY_13,
  GLUT_BITMAP_9_BY_15,
  GLUT_BITMAP_TIMES_ROMAN_10,
  GLUT_BITMAP_TIMES_ROMAN_24,
  GLUT_BITMAP_HELVETICA_10,
  GLUT_BITMAP_HELVETICA_18
};
static int font = 0;

void writeBitmapString(void *font, char *string)
{
  for (char *c = string; *c; c++) glutBitmapCharacter(font, *c);
}

void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);
  glRasterPos3f(5.0, 50.0, 0.0);
  writeBitmapString(fonts[font], "I am having so much fun with OpenGL it can't be legal!");
  
  glFlush();
}

void setup(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 1.0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
  switch (key)
    {
    case 27:
      exit(0);
      break;    
    }
}

void specialKeyInput(int key, int x, int y)
{
  switch (key)
    {
    case GLUT_KEY_LEFT:
      font--;
      break;
    case GLUT_KEY_RIGHT:
      font++;
      break;
    }
  font %= sizeof(fonts) / sizeof(void*);
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(700, 500);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("window");
  glutDisplayFunc(drawScene);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);
  glutSpecialFunc(specialKeyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup();

  glutMainLoop();
}
