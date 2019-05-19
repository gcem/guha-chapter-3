//
// Writes a text using various line stipple patterns
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
static int stippleID = 0;
static void *font = GLUT_STROKE_ROMAN;

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

  glLineWidth(1.5);

  glDisable(GL_LINE_STIPPLE);

  glPushMatrix();
  glTranslatef(5.0, 30.0, 0.0);
  glScalef(0.02, 0.02, 0.02);
  strokeString(font, "I am having so much fun with OpenGL it can't be legal!");
  glPopMatrix();
  
  glEnable(GL_LINE_STIPPLE);

  glPushMatrix();
  glLineStipple(1, 0x5555);
  glTranslatef(5.0, 40.0, 0.0);
  glScalef(0.02, 0.02, 0.02);
  strokeString(font, "I am having so much fun with OpenGL it can't be legal!");
  glPopMatrix();
  
  glPushMatrix();
  glLineStipple(1, 0x0101);
  glTranslatef(5.0, 50.0, 0.0);
  glScalef(0.02, 0.02, 0.02);
  strokeString(font, "I am having so much fun with OpenGL it can't be legal!");
  glPopMatrix();
  
  glPushMatrix();
  glLineStipple(1, 0x00FF); 
  glTranslatef(5.0, 60.0, 0.0);
  glScalef(0.02, 0.02, 0.02);
  strokeString(font, "I am having so much fun with OpenGL it can't be legal!");
  glPopMatrix();
  
  glPushMatrix();
  glLineStipple(5, 0x5555);
  glTranslatef(5.0, 70.0, 0.0);
  glScalef(0.02, 0.02, 0.02);
  strokeString(font, "I am having so much fun with OpenGL it can't be legal!");
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
  glViewport(0, 0, w, h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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
