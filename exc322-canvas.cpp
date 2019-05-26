//
// This program allows the user to draw simple shapes on a canvas.
//
// Interaction:
// Left click on a box on the left to select a primitive.
// Then left click on the drawing area: once for point, twice for line or rectangle,
// multiple times for polyline
// Middle click to end/cancel current drawing
// Right click for menu options.
//


#include <cstdlib>
#include <vector>
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

#include "exc322-objects.h"

using namespace std;

#define INACTIVE -1
#define POINT 0
#define LINE 1
#define POLYLINE 2
#define RECTANGLE 3
#define CIRCLE 4
#define NUMBERPRIMITIVES 5

// Use the STL extension of C++.
using namespace std;

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?


float Point::size = pointSize; // Set point size.

// Vectors of primitives
vector<Point> points;
vector<Line> lines;
vector<Rect> rectangles;

// Iterators to traverse primitive arrays
vector<Point>::iterator pointsIterator; 
vector<Line>::iterator linesIterator;
vector<Rect>::iterator rectanglesIterator;

// Function to draw all points in the points array.
void drawPoints(void)
{
  // Loop through the points array drawing each point.
  pointsIterator = points.begin();
  while(pointsIterator != points.end() )
    {
      pointsIterator->drawPoint(pointSize);
      pointsIterator++;
    }
}

// Function to draw all lines in the lines array.
void drawLines(void)
{
  // Loop through the lines array drawing each line.
  linesIterator = lines.begin();
  while(linesIterator != lines.end() )
    {
      linesIterator->drawLine();
      linesIterator++;
    }
}


// Function to draw all rectangles in the rectangles array.
void drawRectangles(void)
{
  // Loop through the rectangles array drawing each rectangle.
  rectanglesIterator = rectangles.begin();
  while(rectanglesIterator != rectangles.end() )
    {
      rectanglesIterator->drawRectangle();
      rectanglesIterator++;
    }
}

// draw empty selection boxes to draw icons in
void drawSelectionBoxes()
{
  for (int i = 0; i < NUMBERPRIMITIVES; i++)
    {
      if (primitive == i) glColor3f(1.0, 1.0, 1.0); // Highlight.
      else glColor3f(0.8, 0.8, 0.8); // No highlight.
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glRectf(0.0, (1 - i / 10.0) * height, 0.1*width, -height);
      
      // Draw black boundary.
      glColor3f(0.0, 0.0, 0.0); 
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glRectf(0.0, (1 - i / 10.0) * height, 0.1*width, -height); 

    }
}


// Function to draw point selection box in left selection area.
void drawPointSelectionIcon(void)
{  
  // Draw point icon.
  glPointSize(pointSize);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  glVertex3f(0.05*width, 0.95*height - height * POINT / 10.0, 0.0);
  glEnd();  
}

// Function to draw line selection box in left selection area.
void drawLineSelectionIcon(void)
{  
  // Draw line icon.
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.025*width, 0.925*height - height * LINE / 10.0, 0.0);
  glVertex3f(0.075*width, 0.975*height - height * LINE / 10.0, 0.0);
  glEnd();  
}

void drawPolyLineSelectionIcon()
{
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINE_STRIP);
  glVertex3f(0.02*width, 0.925*height - height * POLYLINE / 10.0, 0.0);
  glVertex3f(0.045*width, 0.975*height - height * POLYLINE / 10.0, 0.0);
  glVertex3f(0.055*width, 0.925*height - height * POLYLINE / 10.0, 0.0);
  glVertex3f(0.08*width, 0.975*height - height * POLYLINE / 10.0, 0.0);
  glEnd();
}

// Function to draw rectangle selection box in left selection area.
void drawRectangleSelectionIcon(void)
{  
  // Draw rectangle icon.
  glColor3f(0.0, 0.0, 0.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glRectf(0.025*width,
	  0.935*height - height * RECTANGLE / 10.0, 0.075*width,
	  0.965*height - height * RECTANGLE / 10.0);
  glEnd();  
}

// Function to draw unused part of left selection area.
void drawInactiveArea(void)
{
  glColor3f(0.6, 0.6, 0.6);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);

  glColor3f(0.0, 0.0, 0.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);
}

// Function to draw temporary point.
void drawTempPoint(void)
{
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(pointSize);
  glBegin(GL_POINTS);
  glVertex3f(tempX, tempY, 0.0);
  glEnd(); 
}

// Function to draw a grid.
void drawGrid(void)
{
  int i;
   
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0x5555); 
  glColor3f(0.75, 0.75, 0.75);

  glBegin(GL_LINES);
  for (i=2; i <=9; i++)
    {
      glVertex3f(i*0.1*width, 0.0, 0.0);
      glVertex3f(i*0.1*width, height, 0.0);
    }
  for (i=1; i <=9; i++)
    {
      glVertex3f(0.1*width, i*0.1*height, 0.0);
      glVertex3f(width, i*0.1*height, 0.0);
    }
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

// Drawing routine.
void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0); 

  drawSelectionBoxes();
  drawPointSelectionIcon();
  drawLineSelectionIcon();
  drawPolyLineSelectionIcon();
  drawRectangleSelectionIcon();
  drawInactiveArea();

  drawPoints();
  drawLines();
  drawRectangles();

  if(pointCount == 1) drawTempPoint();
  if (isGrid) drawGrid();

  glutSwapBuffers();
}

// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y)
{
  int primitiveIndex = 10 * (height - y) / height; // round down the result
  if (primitiveIndex >= NUMBERPRIMITIVES) primitive = INACTIVE;
  else primitive = primitiveIndex;
}

// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
      y = height - y; // Correct from mouse to OpenGL co-ordinates.

      
      // Click outside canvas - do nothing.
      if ( x < 0 || x > width || y < 0 || y > height ) ;

      // Click in left selection area.
      else if ( x < 0.1*width ) 
	{
	  pickPrimitive(y);
	  pointCount = 0;
	}

      // Click in canvas.
      else
	{
	  if (primitive == POINT) points.push_back( Point(x,y) );
	  else if (primitive == LINE) 
	    { 
	      if (pointCount == 0)
		{
		  tempX = x; tempY = y;
		  pointCount++;
		}
	      else 
		{
		  lines.push_back( Line(tempX, tempY, x, y) );
		  pointCount = 0;
		}	      
	    }
	  else if (primitive == POLYLINE) 
	    { 
	      if (pointCount == 0)
		{
		  tempX = x; tempY = y;
		  pointCount++;
		}
	      else 
		{
		  lines.push_back( Line(tempX, tempY, x, y) );
		  tempX = x; tempY = y;
		}
	    }
	  else if (primitive == RECTANGLE) 
	    { 
	      if (pointCount == 0)
		{
		  tempX = x; tempY = y;
		  pointCount++;
		}
	      else 
		{
		  rectangles.push_back( Rect(tempX, tempY, x, y) );
		  pointCount = 0;
		}
	    }
	}
    }
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
      pointCount = 0;
    }
  glutPostRedisplay();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set viewing box dimensions equal to window dimensions.
  glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
   
  // Pass the size of the OpenGL window to globals.
  width = w; 
  height = h;  

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch (key) 
    {
    case 27:
      exit(0);
      break;
    default:
      break;
    }
}

// Clear the canvas and reset for fresh drawing.
void clearAll(void)
{
  points.clear();
  lines.clear();
  rectangles.clear();
  primitive = INACTIVE;
  pointCount = 0;
}

// The right button menu callback function.
void rightMenu(int id)
{
  if (id==1) 
    {
      clearAll();
      glutPostRedisplay();
    }
  if (id==2) exit(0);
}

// The sub-menu callback function.
void grid_menu(int id)
{
  if (id==3) isGrid = 1;
  if (id==4) isGrid = 0;
  glutPostRedisplay();
}

// Function to create menu.
void makeMenu(void)
{
  int sub_menu;
  sub_menu = glutCreateMenu(grid_menu);
  glutAddMenuEntry("On", 3);
  glutAddMenuEntry("Off",4);

  glutCreateMenu(rightMenu);
  glutAddSubMenu("Grid", sub_menu);
  glutAddMenuEntry("Clear",1);
  glutAddMenuEntry("Quit",2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialization routine.
void setup(void) 
{
  glClearColor(1.0, 1.0, 1.0, 0.0); 

  makeMenu(); // Create menu.
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
  cout << "Interaction:" << endl;
  cout << "Left click on a box on the left to select a primitive." << endl
       << "Then left click on the drawing area: once for point, twice for line or rectangle." << endl
       << "Right click for menu options." <<  endl; 
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
  glutCreateWindow("canvas.cpp");
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);
  glutMouseFunc(mouseControl); 

  glewExperimental = GL_TRUE;
  glewInit();

  setup(); 

  glutMainLoop(); 
}
