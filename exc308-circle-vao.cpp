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
static int numVertices = 7;
static float *vertices = NULL;
static float *colors = NULL;
static unsigned int buffer[1];
static unsigned int vao[1];

static int sizeVertices;

void fillVertices()
{
  int i, index = 0;
  float angle;

  vertices = new float[numVertices * 3];
  sizeVertices = numVertices * 3 * sizeof(float);
  
  for (i = 0; i < numVertices; i++)
    {
      angle = 2 * PI * i / numVertices;
      vertices[index++] = X + R * cos(angle);
      vertices[index++] = Y + R * sin(angle);
      vertices[index++] = 0;
    }
}

void fillColors()
{
  int i, index = 0;

  colors = new float[numVertices * 3];
  
  for (i = 0; i < numVertices; i++)
    {
      colors[index++] = (float) rand() / (float) RAND_MAX;
      colors[index++] = (float) rand() / (float) RAND_MAX;
      colors[index++] = (float) rand() / (float) RAND_MAX;
    }
}

void updateVBO()
{
  glBindVertexArray(vao[0]);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeVertices, NULL, GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVertices, vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeVertices, sizeVertices, colors);

  glColorPointer(3, GL_FLOAT, 0, (void*) (sizeVertices));
}

void initVBO()
{
  glBindVertexArray(vao[0]);
  glGenBuffers(1, buffer);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  
  glVertexPointer(3, GL_FLOAT, 0, 0);
}

// Drawing routine.
void drawScene(void)
{  
   float t = 0; // Angle parameter.
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(0.0, 0.0, 0.0);

   glBindVertexArray(vao[0]);
   glDrawArrays(GL_LINE_LOOP, 0, numVertices);
   
   glFlush();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0);

   glGenVertexArrays(1, vao);
   
   initVBO();

   fillVertices();
   fillColors();
   updateVBO();
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
	 fillVertices();
	 fillColors();
	 updateVBO();
         glutPostRedisplay();
         break;
      case '-':
         if (numVertices > 3) numVertices--;
	 fillVertices();
	 fillColors();
	 updateVBO();
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
