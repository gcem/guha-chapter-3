///////////////////////////////////////////////////////////////////////////////////////          
// hemisphere.cpp
//
// This program approximates a hemisphere with an array of latitudinal triangle strips.
// It stores the full list of vertices in an array to avoid calculating them on each call
// to drawScene
//
// Interaction:
// Press P/p to increase/decrease the number of longitudinal slices.
// Press Q/q to increase/decrease the number of latitudinal slices.
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

using namespace std;

// Globals.
static float R = 5.0; // Radius of hemisphere.
static int p = 6; // Number of longitudinal slices.
static int q = 4; // Number of latitudinal slices.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.
static float *vertices = NULL;
static unsigned int *indices = NULL;

// Calculates the vertex coordinates and stores them in vertices
// Creates the indices array
void updateVertexArray()
{
  int i, j;
  
  // allocate vertex array
  free(vertices);
  if ((vertices = (float*) malloc(3 * p * (q + 1) * sizeof(float))) == NULL) exit(1);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  
  // allocate index array
  free(indices);
  if ((indices = (unsigned int*) malloc(2 * (p + 1) * (q + 1) * sizeof(unsigned int))) == NULL) exit(1);

  // find vertex coordinates and create the index list, line by line
  for (i = 0; i <= q; i++)
    {
      for (j = 0; j < p; j++)
	{	  
	  vertices[p * i * 3 + j * 3] = R * cos(PI / 2 * i / q)  * cos(2 * PI * j / p); // x
	  vertices[p * i * 3 + j * 3 + 1] = R * sin(PI / 2 * i / q); // y
	  vertices[p * i * 3 + j * 3 + 2] = R * cos(PI / 2 * i / q)  * sin(2 * PI * j / p); // z

	  indices[2 * i * (p + 1) + 2 * j] = i * p + j;
	  indices[2 * i * (p + 1) + 2 * j + 1] = (i + 1) * p + j;
	}
      // repeat the first two vertices
      indices[2 * i * (p + 1) + 2 * p] = i * p;
      indices[2 * i * (p + 1) + 2 * p + 1] = (i + 1) * p;
    }
}

// Initialization routine.
void setup(void) 
{
  glEnableClientState(GL_VERTEX_ARRAY);
    
  updateVertexArray();
  glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// Drawing routine.
void drawScene(void)
{
  int  i, j;

  glClear (GL_COLOR_BUFFER_BIT);

  glLoadIdentity();

  // Command to push the hemisphere, which is drawn centered at the origin, 
  // into the viewing frustum.
  glTranslatef(0.0, 0.0, -10.0);

  // Commands to turn the hemisphere.
  glRotatef(Zangle, 0.0, 0.0, 1.0);
  glRotatef(Yangle, 0.0, 1.0, 0.0);
  glRotatef(Xangle, 1.0, 0.0, 0.0);
   
  // Hemisphere properties.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);

  // Array of latitudinal triangle strips, each parallel to the equator, stacked one
  // above the other from the equator to the north pole.
  for (i = 0; i < q; i++)
    {
      // draw the i-th strip
      glDrawElements(GL_TRIANGLE_STRIP, 2 * (p + 1), GL_UNSIGNED_INT, indices + 2 * i * (p + 1));
    }

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
    case 'P':
      p += 1;
      updateVertexArray();
      glutPostRedisplay();
      break;
    case 'p':
      if (p > 3) p -= 1;
      updateVertexArray();
      glutPostRedisplay();
      break;
    case 'Q':
      q += 1;
      updateVertexArray();
      glutPostRedisplay();
      break;
    case 'q':
      if (q > 3) q -= 1;
      updateVertexArray();
      glutPostRedisplay();
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

