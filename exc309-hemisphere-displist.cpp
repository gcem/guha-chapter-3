///////////////////////////////////////////////////////////////////////////////////////          
// hemisphere.cpp
//
// This program approximates a hemisphere with an array of latitudinal triangle strips.
//
// Interaction:
// Press x, X, y, Y, z, Z to turn the hemisphere.
//
// Sumanta Guha.
/////////////////////////////////////////////////////////////////////////////////////// 

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

#define PI 3.14159265
#define P 12 // Number of longitudinal slices.
#define Q 12 // Number of latitudinal slices.

using namespace std;

// Globals.
static float R = 5.0; // Radius of hemisphere.

static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.
static int hemisphereDL; // display list for drawing a hemisphere

// Initialization routine.
void setup(void) 
{
  int  i, j;
  
  glClearColor(1.0, 1.0, 1.0, 0.0);

  hemisphereDL = glGenLists(1);

  glNewList(hemisphereDL, GL_COMPILE);
   
  // Hemisphere properties.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);

  // Array of latitudinal triangle strips, each parallel to the equator, stacked one
  // above the other from the equator to the north pole.
  for(j = 0; j < Q; j++)
    {
      // One latitudinal triangle strip.
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= P; i++)
	{
	  glVertex3f( R * cos( (float)(j+1)/Q * PI/2.0 ) * cos( 2.0 * (float)i/Q * PI ),
		      R * sin( (float)(j+1)/Q * PI/2.0 ),
		      R * cos( (float)(j+1)/Q * PI/2.0 ) * sin( 2.0 * (float)i/P * PI ) );
	  glVertex3f( R * cos( (float)j/Q * PI/2.0 ) * cos( 2.0 * (float)i/P * PI ),
		      R * sin( (float)j/Q * PI/2.0 ),
		      R * cos( (float)j/Q * PI/2.0 ) * sin( 2.0 * (float)i/P * PI ) );         
	}
      glEnd();
    }

  glEndList();   
}

// Drawing routine.
void drawScene(void)
{
  glClear (GL_COLOR_BUFFER_BIT);

  // draw the upper half
  glPushMatrix();
  glTranslatef(0.0, 0.0, -10.0);
  glRotatef(Zangle, 0.0, 0.0, 1.0);
  glRotatef(Yangle, 0.0, 1.0, 0.0);
  glRotatef(Xangle, 1.0, 0.0, 0.0);
  glCallList(hemisphereDL);
  glPopMatrix();

  // draw the lower half by scaling Y by -1
  glPushMatrix();
  glTranslatef(0.0, 0.0, -10.0);
  glRotatef(Zangle, 0.0, 0.0, 1.0);
  glRotatef(Yangle, 0.0, 1.0, 0.0);
  glRotatef(Xangle, 1.0, 0.0, 0.0);
  glScalef(1.0, -1.0, 1.0);
  glCallList(hemisphereDL);
  glPopMatrix();
   
  glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, w, h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
    {
    case 27:
      exit(0);
      break;
    case 'x':
      Xangle += 5.0;
      if (Xangle > 360.0) Xangle -= 360.0;
      glutPostRedisplay();
      break;
    case 'X':
      Xangle -= 5.0;
      if (Xangle < 0.0) Xangle += 360.0;
      glutPostRedisplay();
      break;
    case 'y':
      Yangle += 5.0;
      if (Yangle > 360.0) Yangle -= 360.0;
      glutPostRedisplay();
      break;
    case 'Y':
      Yangle -= 5.0;
      if (Yangle < 0.0) Yangle += 360.0;
      glutPostRedisplay();
      break;
    case 'z':
      Zangle += 5.0;
      if (Zangle > 360.0) Zangle -= 360.0;
      glutPostRedisplay();
      break;
    case 'Z':
      Zangle -= 5.0;
      if (Zangle < 0.0) Zangle += 360.0;
      glutPostRedisplay();
      break;
    default:
      break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
  cout << "Interaction:" << endl;
  cout << "Press P/p to increase/decrease the number of longitudinal slices." << endl
       << "Press Q/q to increase/decrease the number of latitudinal slices." << endl
       << "Press x, X, y, Y, z, Z to turn the hemisphere." << endl;
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
  glutCreateWindow("hemisphere.cpp");
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup(); 
   
  glutMainLoop(); 
}

