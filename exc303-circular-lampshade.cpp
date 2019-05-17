// 
// circular lampshade
//
// Interaction:
// space: switch between wireframe and filled
//

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
#define VERTICES 40

using namespace std;

static float R = 30.0;
static int wire = 1;
static float vertices[VERTICES * 3 * 2];
static int indices[(VERTICES + 1) * 2];

void calculateVertices()
{
  int i, index = 0;
  for (i = 0; i < VERTICES; i++)
    {
      vertices[index++] = R * cos(2.0 * PI * i / VERTICES);
      vertices[index++] = -20.0;
      vertices[index++] = R * sin(2.0 * PI * i / VERTICES);
      
      vertices[index++] = (R / 2 * cos(2.0 * PI * i / VERTICES));
      vertices[index++] = 20.0;
      vertices[index++] = R / 2 * sin(2.0 * PI * i / VERTICES);
    }
}

void initIndices()
{
  int i;
  for (i = 0; i < VERTICES * 2; i++)
    indices[i] = i;
  indices[VERTICES * 2] = 0;
  indices[VERTICES * 2 + 1] = 1;
}

// Initialization routine.
void setup(void) 
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  calculateVertices();
  initIndices();

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
}

// Drawing routine.
void drawScene(void)
{
  int  i, j;

  glClear (GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  glTranslatef(0.0, 0.0, -50.0);
  
  glColor3f(0.0, 0.0, 0.0);
  if (wire)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glDrawElements(GL_TRIANGLE_STRIP, (VERTICES + 1) * 2, GL_UNSIGNED_INT, indices);
  
  glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, w, h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch (key)
    {
    case 27:
      exit(0);
      break;
    case ' ':
      wire = !wire;
      break;
    }
  glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
  cout << "Interaction:" << endl;
  cout << "Press space to switch between filled and wireframe modes" << endl;
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
  glutCreateWindow("lampshade");
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup(); 
   
  glutMainLoop(); 
}

