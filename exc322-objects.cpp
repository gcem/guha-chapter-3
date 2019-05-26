#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>

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

#include "exc322-objects.h"
#define PI 3.14159265358979324

using namespace std;
// Function to draw a point.
void Point::drawPoint(float size)
{  
  glPointSize(size);
  glColor3fv(color);
  glBegin(GL_POINTS);
  glVertex3f(x, y, 0.0);
  glEnd();   
}

// Function to draw a line.
void Line::drawLine()
{
  glColor3fv(color);
  glBegin(GL_LINES);
  glVertex3f(x1, y1, 0.0);
  glVertex3f(x2, y2, 0.0);
  glEnd();
}

// Function to draw a rectangle.
void Rect::drawRectangle()
{
  glColor3fv(color);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glRectf(x1, y1, x2, y2);
}

void Circle::draw(int vertexCount, float angle)
{
  glColor3fv(color);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < vertexCount; i++)
    {
      angle += 2 * PI / vertexCount;
      glVertex3f(x + r * cos(angle), y + r * sin(angle), 0.0);
      cout << y + r * sin(angle) << endl;
    }
  glEnd();
}

void Text::drawText()
{
  glColor3fv(color);
  glPushMatrix();
  glTranslatef(x, y, 0.0);
  glScalef(scale, scale, 1.0);
  for (int i = 0; i < this->length(); i++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, (*this)[i]);
  glPopMatrix();
}
