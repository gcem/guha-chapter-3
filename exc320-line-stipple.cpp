//
// Draws a circle with various line stipple patterns
//
// Interaction:
// +/-: change number of vertices
// space: cycle through line stipple patterns
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

#define PI 3.14159265358979324

using namespace std;

// Globals.
static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int numVertices = 20; // Number of vertices on circle.
static int stippleID = 0;

// Drawing routine.
void drawScene(void)
{  
  float t = 0; // Angle parameter.
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);

  glEnable(GL_LINE_STIPPLE);

  switch(stippleID) 
    {
    case 0: 
      glDisable(GL_LINE_STIPPLE);
      break;	
    case 1: 
      glLineStipple(1, 0x5555); 
      break;	  
    case 2:
      glLineStipple(1, 0x0101);
      break;
    case 3: 
      glLineStipple(1, 0x00FF); 
      break;	  
    case 4:
      glLineStipple(5, 0x5555);
      break;
    }
  
  // Draw a line loop with vertices at equal angles apart on a circle
  // with center at (X, Y) and radius R, The vertices are colored randomly.
  glBegin(GL_LINE_LOOP);
  for(i = 0; i < numVertices; ++i)
    {
      glColor3f((float)rand()/(float)RAND_MAX,
		(float)rand()/(float)RAND_MAX,
		(float)rand()/(float)RAND_MAX); 
      glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
      t += 2 * PI / numVertices;
    }
  glEnd();

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
    case '+':
      numVertices++;
      glutPostRedisplay();
      break;
    case '-':
      if (numVertices > 3) numVertices--;
      glutPostRedisplay();
      break;
    case ' ':
      stippleID++;
      stippleID %= 5;
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
  cout << "Press +/- to increase/decrease the number of vertices on the circle." << endl;
  cout << "Press spacebar to cycle through line stipple patterns." << endl;  
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
