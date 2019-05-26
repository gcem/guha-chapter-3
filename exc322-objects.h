#ifndef H_E322_OBJECTS
#define H_E322_OBJECTS

// Point class.
class Point
{
public:
  Point(int xVal, int yVal)
  {
    x = xVal; y = yVal;
  }
  void drawPoint(float); // Function to draw a point.
private:
  int x, y; // x and y co-ordinates of point.
  static float size; // Size of point.
};

// Line class.
class Line
{
public:
  Line(int x1Val, int y1Val, int x2Val, int y2Val)
  {
    x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
  }
  void drawLine();
private:
  int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};

// Rectangle class.
class Rect
{
public:
  Rect(int x1Val, int y1Val, int x2Val, int y2Val)
  {
    x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
  }
  void drawRectangle();
private:
  int x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
};

#endif
