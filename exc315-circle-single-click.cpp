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

#define VERTICES 40
#define PI 3.14159265358979324

using namespace std;

static int width = 500;
static int height = 500;
static int centerX, centerY; // in window coordinates (pixels)
static float radius;

class Circle
{
public:
  Circle(float x = 0, float y = 0, float r = 0)
    : x { x }, y { y }, r { r }  
  {
  }

  void setRadius(float r) { this->r = r; }
  
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
}

void reshape(int w, int h)
{
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
  float rx, ry;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
      centerX = x;
      centerY = y;
      rx = (x - centerX) / (float) width;
      ry = (y - centerY) / (float) height;
      radius = 100.0 * sqrt(rx * rx + ry * ry);
      currentCircle = Circle(centerX * 100.0 / width,
			     (height - centerY) * 100.0 / height,
			     radius);
      glutPostRedisplay();
    }    
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
      circles.push_back(currentCircle);
      glutPostRedisplay;
    }
  else if (button == GLUT_RIGHT_BUTTON) exit(0);
}

void mouseMotion(int x, int y)
{
  float rx, ry;
  rx = (x - centerX) / (float) width;
  ry = (y - centerY) / (float) height;
  currentCircle.setRadius(100.0 * sqrt(rx * rx + ry * ry));
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
  glutMotionFunc(mouseMotion);

  glewExperimental = GL_TRUE;
  glewInit();

  setup();
  
  glutMainLoop();
}
