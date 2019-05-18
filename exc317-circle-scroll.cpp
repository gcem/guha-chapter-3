//
// Draws a circle with mouse: Press and drag
// with the left mouse button to draw the circle
//
// This is a modified version of exc315-circle-motion
// There may be some redundant code left
//

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")

#ifndef GLUT_SCROLL_UP
#define GLUT_SCROLL_UP 3
#define GLUT_SCROLL_DOWN 4
#endif

#define VERTICES 40
#define PI 3.14159265358979324

using namespace std;

static int width = 500;
static int height = 500;
static float radius = 10;

class Circle
{
public:
  Circle(float x = 0, float y = 0, float r = 0)
    : x { x }, y { y }, r { r }  
  {
  }

  void setRadius(float r) { this->r = r; }
  void setX(float x) { this->x = x; }
  void setY(float y) { this->y = y; }

  float getRadius() { return r; }
  
  void draw();
private:
  float x, y, r;
};

void Circle::draw()
{
  float angle;

  glColor3f(0.0, 0.0, 0.0);
  
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < VERTICES; i++)
    {
      angle = 2 * PI * i / (float) VERTICES;
      glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
  glEnd();
}

vector<Circle> circles;
Circle currentCircle;

void draw()
{
  vector<Circle>::const_iterator end = circles.end();
  vector<Circle>::iterator current = circles.begin();
  
  glClear(GL_COLOR_BUFFER_BIT);

  while (current != end)
    {
      current++->draw();
    }

  currentCircle.draw();
  
  glFlush();
}


void setup()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  currentCircle.setRadius(radius);
  currentCircle.setX(-100000);
  currentCircle.setY(-100000);
}

void reshape(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
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
    }
}

void mouseInput(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
      circles.push_back(currentCircle);
      glutPostRedisplay();
    }
  else if (button == GLUT_SCROLL_UP && state == GLUT_DOWN) currentCircle.setRadius(currentCircle.getRadius() + 3);
  else if (button == GLUT_SCROLL_DOWN && state == GLUT_DOWN && currentCircle.getRadius() > 3) currentCircle.setRadius(currentCircle.getRadius() - 3);
  else if (button == GLUT_RIGHT_BUTTON) exit(0);
  
}

void mousePassiveMotion(int x, int y)
{
  currentCircle.setX(x * 100.0 / width);
  currentCircle.setY((height - y) * 100.0 / height);
		     
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("window");
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyInput);
  glutMouseFunc(mouseInput);
  glutPassiveMotionFunc(mousePassiveMotion);

  glewExperimental = GL_TRUE;
  glewInit();

  setup();
  
  glutMainLoop();
}
