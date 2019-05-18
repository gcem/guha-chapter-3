//
// Draws a circle after two left clicks: First click picks the
// center, second click a point on the circle.
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
static int centerChosen = 0;

class Circle
{
public:
  Circle(float x, float y, float r)
    : x { x }, y { y }, r { r }  
  {
  }
  
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

void draw()
{
  vector<Circle>::const_iterator end = circles.end();
  vector<Circle>::iterator current = circles.begin();
  
  glClear(GL_COLOR_BUFFER_BIT);

  while (current != end)
    {
      current++->draw();
    }
  
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
      if (!centerChosen)
	{
	  centerX = x;
	  centerY = y;
	}
      else
	{
	  rx = (x - centerX) / (float) width;
	  ry = (y - centerY) / (float) height;
	  radius = 100.0 * sqrt(rx * rx + ry * ry);
	  circles.push_back(Circle(centerX * 100.0 / width,
				       (height - centerY) * 100.0 / height,
				       radius));
	  glutPostRedisplay();
	}
      centerChosen = !centerChosen;
    }
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

  glewExperimental = GL_TRUE;
  glewInit();

  setup();
  
  glutMainLoop();
}
