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

#include <cmath>
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
#define HEXAGON 5
#define TEXT 6
#define NUMBERPRIMITIVES 7

// Use the STL extension of C++.
using namespace std;

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?
static int isFilled[NUMBERPRIMITIVES] = {0};
static int gridSize = 10;
static float colors[NUMBERPRIMITIVES][3] = {0};
static int mouseOnPrimitive = INACTIVE;

int grid_sub, size_sub, color_sub, mode_sub; // menu ids
int menuState = 0;
void rightMenu(int);


float Point::size = pointSize; // Set point size.

Line currentLine;
Rect currentRect;
Circle currentCircle;
Hexagon currentHexagon;
Text currentText;

// Vectors of primitives
vector<Point> points;
vector<Line> lines;
vector<Rect> rectangles;
vector<Circle> circles;
vector<Hexagon> hexagons;
vector<Text> texts;

// Function to draw all points in the points array.
void drawPoints(void)
{
  vector<Point>::iterator iter;
  vector<Point>::const_iterator end; 
  // Loop through the points array drawing each point.
  iter = points.begin();
  end = points.end();
  while(iter != points.end() )
    {
      iter->drawPoint(pointSize);
      iter++;
    }
}

// Function to draw all lines in the lines array.
void drawLines(void)
{
  vector<Line>::iterator iter;
  vector<Line>::const_iterator end; 
  // Loop through the lines array drawing each line.
  iter = lines.begin();
  end = lines.end();
  while(iter != end)
    {
      iter->drawLine();
      iter++;
    }
}

// draw circles
void drawCircles()
{
  vector<Circle>::iterator iter;
  vector<Circle>::const_iterator end; 
  iter = circles.begin();
  end = circles.end();
  while (iter != circles.end())
    {
      iter->drawCircle();
      iter++;
    }
}

void drawHexagons()
{
  vector<Hexagon>::iterator iter;
  vector<Hexagon>::const_iterator end; 
  iter = hexagons.begin();
  end = hexagons.end();
  while (iter != hexagons.end())
    {
      iter->drawHexagon();
      iter++;
    }
}

// Function to draw all rectangles in the rectangles array.
void drawRectangles(void)
{
  vector<Rect>::iterator iter;
  vector<Rect>::const_iterator end; 
  // Loop through the rectangles array drawing each rectangle.
  iter = rectangles.begin();
  end = rectangles.end();
  
  while(iter != end)
    {
      iter->drawRectangle();
      iter++;
    }
}

void drawTexts()
{
  vector<Text>::iterator iter;
  vector<Text>::const_iterator end; 
  // Loop through the rectangles array drawing each rectangle.
  iter = texts.begin();
  end = texts.end();
  
  while(iter != end)
    {
      iter->drawText();
      iter++;
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
  glColor3fv(colors[POINT]);
  glBegin(GL_POINTS);
  glVertex3f(0.05*width, 0.95*height - height * POINT / 10.0, 0.0);
  glEnd();  
}

// Function to draw line selection box in left selection area.
void drawLineSelectionIcon(void)
{  
  // Draw line icon.
  glColor3fv(colors[LINE]);
  glBegin(GL_LINES);
  glVertex3f(0.025*width, 0.925*height - height * LINE / 10.0, 0.0);
  glVertex3f(0.075*width, 0.975*height - height * LINE / 10.0, 0.0);
  glEnd();  
}

void drawPolyLineSelectionIcon()
{
  glColor3fv(colors[POLYLINE]);
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
  glColor3fv(colors[RECTANGLE]);
  glPolygonMode(GL_FRONT_AND_BACK, isFilled[RECTANGLE] ? GL_FILL : GL_LINE);
  glRectf(0.025*width,
	  0.935*height - height * RECTANGLE / 10.0, 0.075*width,
	  0.965*height - height * RECTANGLE / 10.0);
  glEnd();  
}

void drawCircleSelectionIcon(void)
{
  Circle icon =
    Circle(0.05*width, 0.95*height - height * CIRCLE / 10.0, 0.035 * min(width, height));
  icon.setColor(colors[CIRCLE]);
  icon.setMode(isFilled[CIRCLE]);
  icon.drawCircle();
}

void drawHexagonSelectionIcon(void)
{
  Hexagon icon =
    Hexagon(0.05*width, 0.95*height - height * HEXAGON / 10.0,
	    0.05*width + 0.035 * min(width, height), 0.95*height - height * HEXAGON / 10.0);
  icon.setColor(colors[HEXAGON]);
  icon.setMode(isFilled[HEXAGON]);
  icon.drawHexagon();
}

void drawTextSelectionIcon(void)
{
  glColor3fv(colors[TEXT]);
  glPushMatrix();
  glTranslatef(0.015*width, 0.915*height - height * TEXT / 10.0, 0.0);
  glScalef(0.12 * width / 500, 0.33 * height / 500, 1.0);
  glPointSize(1);
  glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'a');
  glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'b');
  glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'c');
  glPopMatrix();
  
  // glRasterPos3f(0.22*width, 0.915*height - height * TEXT / 10.0, 0.0);
  // glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
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
  glColor3f(0.5, 0.0, 1.0);
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
  for (i=1; i < gridSize; i++)
    {
      glVertex3f(width * (0.1 + i * 0.9 / gridSize), 0.0, 0.0);
      glVertex3f(width * (0.1 + i * 0.9 / gridSize), height, 0.0);
    }
  for (i=1; i < gridSize; i++)
    {
      glVertex3f(0.1*width, i*height / (float) gridSize, 0.0);
      glVertex3f(width, i*height / (float) gridSize, 0.0);
    }
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

// Drawing routine.
void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0); 
  
  // these should be at the beginning, otherwise they draw over selection boxes
  drawCircles(); 
  drawHexagons();
  drawPoints();
  drawLines();
  drawRectangles();
  drawTexts();

  // draw the active primitive if there is one
  if (pointCount != 0)
    {
      if (primitive == LINE || primitive == POLYLINE) 
	{	      
	  currentLine.drawLine();
	}
      else if (primitive == RECTANGLE) 
	{	
	  currentRect.drawRectangle();
	}
      else if (primitive == CIRCLE)
	{
	  currentCircle.drawCircle();
	}
      else if (primitive == HEXAGON)
	{
	  currentHexagon.drawHexagon();
	}
      else if (primitive == TEXT)
	{
	  currentText.drawText();
	}
    }
  
  drawSelectionBoxes();
  drawPointSelectionIcon();
  drawLineSelectionIcon();
  drawPolyLineSelectionIcon();
  drawRectangleSelectionIcon();
  drawCircleSelectionIcon();
  drawHexagonSelectionIcon();
  drawTextSelectionIcon();
  drawInactiveArea();

  
  if(pointCount) drawTempPoint();
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


void updateMenus(int x, int y)
{
  if (x < 0.1*width)
    {
      mouseOnPrimitive = 10.0 * (height - y) / height;
      if (mouseOnPrimitive == RECTANGLE || mouseOnPrimitive == CIRCLE || mouseOnPrimitive == HEXAGON)
	{
	  if (menuState != 2)
	    {

	      glutCreateMenu(rightMenu);
	      glutAddSubMenu("Color", color_sub);
	      glutAddSubMenu("Mode", mode_sub);
	      glutAddSubMenu("Grid", grid_sub);
	      glutAddMenuEntry("Clear",1);
	      glutAddMenuEntry("Quit",2);
	      glutAttachMenu(GLUT_RIGHT_BUTTON);
	      menuState = 2;
	    }
	}
      else if (mouseOnPrimitive < NUMBERPRIMITIVES)
	{
	  if (menuState != 1)
	    {

	      glutCreateMenu(rightMenu);
	      glutAddSubMenu("Color", color_sub);
	      glutAddSubMenu("Grid", grid_sub);
	      glutAddMenuEntry("Clear",1);
	      glutAddMenuEntry("Quit",2);
	      glutAttachMenu(GLUT_RIGHT_BUTTON);
	      menuState = 1;
	    }
	}
      else if (menuState != 0)
	{
	  mouseOnPrimitive = INACTIVE;
	  glutCreateMenu(rightMenu);
	  glutAddSubMenu("Grid", grid_sub);
	  glutAddMenuEntry("Clear",1);
	  glutAddMenuEntry("Quit",2);
	  glutAttachMenu(GLUT_RIGHT_BUTTON);
	  menuState = 0;		  
	}
    }
  else if (menuState != 0)
    {
      mouseOnPrimitive = INACTIVE;
      menuState = 0;
      glutCreateMenu(rightMenu);
      glutAddSubMenu("Grid", grid_sub);
      glutAddMenuEntry("Clear",1);
      glutAddMenuEntry("Quit",2);
      glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}



// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
  y = height - y; // Correct from mouse to OpenGL co-ordinates.
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
      if (primitive == TEXT)
	{
	  texts.push_back(currentText);
	  currentText.clear();
	  pointCount = 0;
	}
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
	  if (pointCount == 0)
	    {
	      if (primitive == POINT) points.push_back(Point(x,y, colors[primitive]));
	      else if (primitive != INACTIVE)
		{
		  pointCount++;
		  tempX = x;
		  tempY = y;
		  if (primitive == LINE || primitive == POLYLINE) 
		    {	      
		      currentLine = Line(x, y, x, y);
		      currentLine.setColor(colors[primitive]);
		    }
		  else if (primitive == RECTANGLE) 
		    {	
		      currentRect = Rect(x, y, x, y);
		      currentRect.setColor(colors[primitive]);
		      currentRect.setMode(isFilled[primitive]);
		    }
		  else if (primitive == CIRCLE)
		    {
		      currentCircle = Circle(x, y, 0);
		      currentCircle.setColor(colors[primitive]);
		      currentCircle.setMode(isFilled[primitive]);
		    }
		  else if (primitive == HEXAGON)
		    {
		      currentHexagon = Hexagon(x, y, x, y);
		      currentHexagon.setColor(colors[primitive]);
		      currentHexagon.setMode(isFilled[primitive]);
		    }
		  else if (primitive == TEXT)
		    {
		      currentText = Text(x, y, 0.3);
		      currentText.setColor(colors[primitive]);
		    }
		}
	    }
	  else
	    {
	      if (primitive == LINE) 
		{	      
		  lines.push_back(currentLine);
		  pointCount = 0;
		}
	      else if (primitive == POLYLINE) 
		{ 
		  lines.push_back(currentLine);
		  currentLine.setStart(x, y);
		}
	      else if (primitive == RECTANGLE) 
		{	
		  rectangles.push_back(currentRect);
		  pointCount = 0;
		}
	      else if (primitive == CIRCLE)
		{
		  circles.push_back(currentCircle);
		  pointCount = 0;
		}
	      else if (primitive == HEXAGON)
		{
		  hexagons.push_back(currentHexagon);
		  pointCount = 0;
		}
	    }
	}
    }
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
      pointCount = 0;
    }
  
  updateMenus(x, y);
  
  glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
  y = height - y;

  if (pointCount != 0)
    {
      if (primitive == LINE || primitive == POLYLINE) 
	{	      
	  currentLine.setEnd(x, y);
	}
      else if (primitive == RECTANGLE) 
	{	
	  currentRect.setEnd(x, y);
	}
      else if (primitive == CIRCLE)
	{
	  currentCircle.setEnd(x, y);
	}
      else if (primitive == HEXAGON)
	{
	  currentHexagon.setEnd(x, y);
	}
      glutPostRedisplay();
    }
  updateMenus(x, y);  
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
  if (key == 27)
    exit(0);
  else if (primitive == TEXT && pointCount)
    {
      if (32 <= key && key <= 127) // typed character in text mode
	currentText.addChar(key);
      else if (key == 13) // carriage return
	{
	  pointCount = 0;
	  texts.push_back(currentText);
	}
      else if (key == 8) // backspace
	currentText.removeChar();
      glutPostRedisplay();
    }
}

// Clear the canvas and reset for fresh drawing.
void clearAll(void)
{
  points.clear();
  lines.clear();
  rectangles.clear();
  circles.clear();
  hexagons.clear();
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

void color_menu(int id)
{
  switch (id)
    {
    case 8:
      colors[mouseOnPrimitive][0] = 0.0;
      colors[mouseOnPrimitive][1] = 0.0;
      colors[mouseOnPrimitive][2] = 0.0;
      
      break;
    case 9:
      colors[mouseOnPrimitive][0] = 1.0;
      colors[mouseOnPrimitive][1] = 0.0;
      colors[mouseOnPrimitive][2] = 0.0;
      
      break;
    case 10:
      colors[mouseOnPrimitive][0] = 0.0;
      colors[mouseOnPrimitive][1] = 0.7;
      colors[mouseOnPrimitive][2] = 0.0;
      
      break;
    case 11:
      colors[mouseOnPrimitive][0] = 0.0;
      colors[mouseOnPrimitive][1] = 0.0;
      colors[mouseOnPrimitive][2] = 1.0;
      
      break;
    }
}

void grid_size_menu(int id)
{
  switch (id)
    {
    case 5:
      gridSize = 15;
      break;
    case 6:
      gridSize = 10;
      break;
    case 7:
      gridSize = 5;
      break;
    }
}

void mode_menu(int id)
{
  switch (id)
    {
    case 12:
      isFilled[mouseOnPrimitive] = 1;
      break;
    case 13:
      isFilled[mouseOnPrimitive] = 0;
      break;
    }
}

// Function to create menu.
void makeMenu(void)
{
  size_sub = glutCreateMenu(grid_size_menu);
  glutAddMenuEntry("Small", 5);
  glutAddMenuEntry("Medium", 6);
  glutAddMenuEntry("Large", 7);
  
  grid_sub = glutCreateMenu(grid_menu);
  glutAddMenuEntry("On", 3);
  glutAddMenuEntry("Off",4);
  glutAddSubMenu("Size", size_sub);

  color_sub = glutCreateMenu(color_menu);
  glutAddMenuEntry("Black", 8);
  glutAddMenuEntry("Red", 9);
  glutAddMenuEntry("Green", 10);
  glutAddMenuEntry("Blue", 11);

  mode_sub = glutCreateMenu(mode_menu);
  glutAddMenuEntry("Filled", 12);
  glutAddMenuEntry("Outlined", 13);

  glutCreateMenu(rightMenu);
  glutAddSubMenu("Grid", grid_sub);
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
  glutPassiveMotionFunc(mouseMotion);

  glewExperimental = GL_TRUE;
  glewInit();

  setup(); 

  glutMainLoop(); 
}
