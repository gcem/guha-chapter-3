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

using namespace std;

// Globals.
static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int numVertices = 5; // Number of vertices on circle.
static float *vertices = NULL;
static float *colors = NULL;

void calculateVertices(void)
{
  float angle = 0;
  free(vertices);
  free(colors);

  vertices = (float*) malloc(numVertices * sizeof(float) * 3);
  colors = (float*) malloc(numVertices * sizeof(float) * 3);

  // calculate vertices
  for (int i = 0; i < numVertices; i++)
    {
      vertices[i * 3] = X + R * cos(angle);
      vertices[i * 3 + 1] = Y + R * sin(angle);
      vertices[i * 3 + 2] = 0.0;
      angle += 2 * PI / numVertices;
    }

  // put random numbers in the color array
  for (int i = 0; i < numVertices * 3; i++)
    {      
      colors[i] = (float)rand()/(float)RAND_MAX;
    }
}

// Drawing routine.
void drawScene(void)
{  
  float t = 0; // Angle parameter.
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0, 0.0, 0.0);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);

  glDrawArrays(GL_LINE_LOOP, 0, numVertices);
   
  glFlush();
}

// Initialization routine.
void setup(void) 
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glClearColor(1.0, 1.0, 1.0, 0.0);
  calculateVertices();
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
      calculateVertices();
      glutPostRedisplay();
      break;
    case '-':
      if (numVertices > 3) numVertices--;
      calculateVertices();
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
