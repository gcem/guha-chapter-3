//
// Writes texts in different viewports
//


#include <cstdlib>
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

using namespace std;

// Globals.
static void *font = GLUT_STROKE_ROMAN;
static int width = 500, height = 500;


void strokeString(void *font, char *string)
{
  for (char *c = string; *c; c++) glutStrokeCharacter(font, *c);
}

// Drawing routine.
void drawScene(void)
{  
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(2.0);

  // upper left
  glViewport(0, height / 2, width / 2, height / 2); 
  glRectf(0.0, 0.0, 100.0, 100.0);
  
  glPushMatrix();
  glTranslatef(25.0, 40.0, 0.0);
  glScalef(0.2, 0.2, 0.2);
  strokeString(font, "This");
  glPopMatrix();

  // upper right
  glViewport(width / 2, height / 2, width / 2, height / 2); 
  glRectf(0.0, 0.0, 100.0, 100.0);
  
  glPushMatrix();
  glTranslatef(43.0, 40.0, 0.0);
  glScalef(0.2, 0.2, 0.2);
  strokeString(font, "is");
  glPopMatrix();

  // lower left
  glViewport(0, 0, width / 2, height / 2); 
  glRectf(0.0, 0.0, 100.0, 100.0);
  
  glPushMatrix();
  glTranslatef(37.0, 40.0, 0.0);
  glScalef(0.2, 0.2, 0.2);
  strokeString(font, "so");
  glPopMatrix();

  // lower right
  glViewport(width / 2, 0, width / 2, height / 2); 
  glRectf(0.0, 0.0, 100.0, 100.0);
  
  glPushMatrix();
  glTranslatef(25.0, 40.0, 0.0);
  glScalef(0.2, 0.2, 0.2);
  strokeString(font, "easy!");
  glPopMatrix();

  glFlush();
}

// Initialization routine.
void setup(void) 
{
  glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  width = w;
  height = h;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
    {
    case 27:
      exit(0);
      break;
    default:
      break;
    }
}

// Main routine.
int main(int argc, char **argv) 
{
  glutInit(&argc, argv);

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100); 
  glutCreateWindow("circle.cpp");
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup(); 
   
  glutMainLoop(); 
}
