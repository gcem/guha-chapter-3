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
  
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(20.0, -20.0, 15.0); // bottom right, front
  glVertex3f(20.0, -20.0, -15.0); // bottom right, back
  glVertex3f(-20.0, -20.0, 15.0);
  glVertex3f(-20.0, -20.0, -15.0);

  glVertex3f(-20.0, 20.0, 15.0);
  glVertex3f(-20.0, 20.0, -15.0); 
  glVertex3f(20.0, 20.0, 15.0);
  glVertex3f(20.0, 20.0, -15.0);

  glVertex3f(20.0, -20.0, 15.0);
  glVertex3f(20.0, -20.0, -15.0);
  glEnd();
  
  //back side
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(-20.0, -20.0, -15.0);
  glVertex3f(20.0, -20.0, -15.0);
  glVertex3f(-20.0, 20.0, -15.0);
  glVertex3f(20.0, 20.0, -15.0);
  glEnd();
  
  glFlush();
}

void setup(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
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
