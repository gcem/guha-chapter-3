// 
// lampshade
//
// Interaction:
// space: switch between wireframe and filled
//
//

#include <cstdlib>
#include <cmath>
#include <iostream>

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#endif


#define PI 3.14159265358979324

using namespace std;

static int wire = 1;
static float vertices[] = {
  -20.0, -20.0, 15.0,
  20.0, -20.0, 15.0,
  20.0, 20.0, 15.0,
  -20.0, 20.0, 15.0,

  -20.0, -20.0, -15.0,
  20.0, -20.0, -15.0,
  20.0, 20.0, -15.0,
  -20.0, 20.0, -15.0,
};
static unsigned int sideIndices[] = {
  0, 4, 1, 5, 2, 6, 3, 7, 0, 4
};
static unsigned int backIndices[] = {
  4, 5, 7, 6
};
static unsigned int *indices[] = {sideIndices, backIndices};
static int count[] = {10, 4};
  

void drawScene(void)
{
  float angle;
  
  glClear(GL_COLOR_BUFFER_BIT);
 
  glLoadIdentity();
  
  glTranslatef(0.0,0.0,-40.0);
  glRotatef(40.0, 1.0, 0.0, 0.0);
   
  glColor3f(0.0, 0.0, 0.0);
  if (wire)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  glMultiDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void**) indices, 2);
  
  glFlush();
}

void setup(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
}

void resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 7.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

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

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("window");
  glutDisplayFunc(drawScene);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);

  glewExperimental = GL_TRUE;
  glewInit();

  setup();

  glutMainLoop();
}
