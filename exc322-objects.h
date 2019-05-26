#ifndef H_E322_OBJECTS
#define H_E322_OBJECTS

#define CIRCLE_VERTICES 40

// Point class.
class Point
{
public:
  Point(int xVal = 0, int yVal = 0)
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
  Line(int x1Val = 0, int y1Val = 0, int x2Val = 0, int y2Val = 0)
  {
    x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
  }
  void drawLine();
  void setStart(float a, float b) { x1 = a; y1 = b; }
  void setEnd(float a, float b) { x2 = a; y2 = b; }
private:
  int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};

// Rectangle class.
class Rect
{
public:
  Rect(int x1Val = 0, int y1Val = 0, int x2Val = 0, int y2Val = 0)
  {
    x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
  }
  void drawRectangle();
  void setStart(float a, float b) { x1 = a; y1 = b; }
  void setEnd(float a, float b) { x2 = a; y2 = b; }
private:
  int x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
};

class Circle
{
 public:
 Circle(float x = 0, float y = 0,  float r = 0)
   : x { x }, y { y }, r { r } { }
 Circle(float x, float y,  float outX, float outY)
    : x { x }, y { y } { r = sqrt((x-outX) * (x - outX) + (y - outY) * (y - outY));}
  void drawCircle() { draw(CIRCLE_VERTICES, 0.0);}
  void setStart(float a, float b) { x = a; y = b; }
  void setEnd(float outX, float outY) { r = sqrt((x-outX) * (x - outX) + (y - outY) * (y - outY));}
 protected:
  float x, y, r;
  void draw(int vertexCount, float angle);
};

class Hexagon : public Circle
{
 public:
 Hexagon(float x = 0, float y = 0, float vertexX = 0, float vertexY = 0) : Circle(x, y, vertexX, vertexY)
    { angle = atan((y - vertexY) / (x-vertexX)); }
  void drawHexagon() { draw(6, angle);}
  void setEnd(float outX, float outY) {
    r = sqrt((x-outX) * (x - outX) + (y - outY) * (y - outY));
    angle = atan((y - outY) / (x-outX));}
 private:
  float angle;
};

#endif
