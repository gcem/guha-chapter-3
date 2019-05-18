/////////////////////////////////////////////////////////////////////         
// circle.cpp
//
// This program draws a line loop with vertices equally apart on 
// a fixed circle. The larger the number of vertices the better
// the loop approximates the circle.
//
// Interaction:
// Press +/- to increase/decrease the number of vertices of the loop. 
//
// Sumanta Guha.
///////////////////////////////////////////////////////////////////// 

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

#define PI 3.14159265358979324
#define VERTICES 20 // Number of vertices on circle.

using namespace std;

// Globals.
static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int circle; // display list to draw a circle

// Drawing routine.
void drawScene(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);

  glPushMatrix();
  glTranslatef(X, Y, 0.0);
  glCallList(circle);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(X, Y, 0.0);
  glScalef(0.8, 0.8, 1.0);
  glCallList(circle);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(X, Y, 0.0);
  glScalef(0.6, 0.6, 1.0);
  glCallList(circle);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(X, Y, 0.0);
  glScalef(0.5, 0.5, 1.0);
  glCallList(circle);
  glPopMatrix();

  glFlush();
}

// Initialization routine.
void setup(void) 
{
  float t = 0; // Angle parameter.
  int i;

  glClearColor(1.0, 1.0, 1.0, 0.0);

  circle = glGenLists(1);

  glNewList(circle, GL_COMPILE);
  
  glBegin(GL_LINE_LOOP);
  for(i = 0; i < VERTICES; ++i)
    {
      glColor3f((float)rand()/(float)RAND_MAX,
		(float)rand()/(float)RAND_MAX,
		(float)rand()/(float)RAND_MAX); 
      glVertex3f(R * cos(t), R * sin(t), 0.0);
      t += 2 * PI / VERTICES;
    }
  glEnd();

  glEndList();
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

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
  cout << "Interaction:" << endl;
  cout << "Press +/- to increase/decrease the number of vertices on the circle." << endl;  
}

// Main routine.
int main(int argc, char **argv) 
{
  printInteraction();
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
