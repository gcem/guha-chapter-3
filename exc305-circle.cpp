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
#define VERTICES 7

using namespace std;

// Globals.
static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static float vertices[VERTICES * 3];
static float colors[VERTICES * 3];
static unsigned int buffer[1];

void fillVertices()
{
  int i, index = 0;
  float angle;
  
  for (i = 0; i < VERTICES; i++)
    {
      angle = 2 * PI * i / VERTICES;
      vertices[index++] = X + R * cos(angle);
      vertices[index++] = Y + R * sin(angle);
      vertices[index++] = 0;
    }
}

void fillColors()
{
  int i, index = 0;
    
  for (i = 0; i < VERTICES; i++)
    {
      colors[index++] = (float) rand() / (float) RAND_MAX;
      colors[index++] = (float) rand() / (float) RAND_MAX;
      colors[index++] = (float) rand() / (float) RAND_MAX;
    }
}

void setVBO()
{
  glGenBuffers(1, buffer);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void*) sizeof(vertices));
}

// Drawing routine.
void drawScene(void)
{  
   float t = 0; // Angle parameter.
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(0.0, 0.0, 0.0);

   glDrawArrays(GL_LINE_LOOP, 0, VERTICES);
   
   glFlush();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
   fillVertices();
   fillColors();
   setVBO();     
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
      // case '+':
      //    numVertices++;
      //    glutPostRedisplay();
      //    break;
      // case '-':
      //    if (numVertices > 3) numVertices--;
      //    glutPostRedisplay();
      //    break;
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
