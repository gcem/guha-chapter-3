// 
// An OpenGL program template based on Samanta Guha's circle.cpp
//
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
#define VERTICES 40

using namespace std;

// Global variables
static float X = 50;
static float Y = 50;
static float R[] = {40.0, 33.0, 26.0, 19.0, 12.0};
static float depth[] = {0.1, 0.2, 0.3, 0.4, 0.5};
static float colorVal[] = {
  0.0, 0.8, 0.0,
  0.9, 0.0, 0.0,
  0.0, 0.0, 0.8,
  0.8, 0.8, 0.0,
  0.7, 0.0, 0.9
};
static float vertices[(VERTICES + 2) * 3 * 5];
static float colors[(VERTICES + 2) * 3 * 5];
static int count[5];
static int first[5];
static unsigned int buffer[1];

void initializeArrays()
{
  float angle;
  int i, j, index = 0;
  // for each circle
  for (i = 0; i < 5; i++)
    {
      // start index and vertex count
      first[i] = (VERTICES + 2) * i;
      count[i] = VERTICES + 2;

      // center
      colors[index] = colorVal[i * 3];
      vertices[index++] = X;
      
      colors[index] = colorVal[i * 3 + 1];
      vertices[index++] = Y;
      
      colors[index] = colorVal[i * 3 + 2];
      vertices[index++] = depth[i];

      // vertices
      for (j = 0; j <= VERTICES; j++)
	{
	  angle = 2 * PI * j / (float) VERTICES;
	  
	  colors[index] = colorVal[i * 3];
	  vertices[index++] = X + cos(angle) * R[i];
	  
	  colors[index] = colorVal[i * 3 + 1];
	  vertices[index++] = Y + sin(angle) * R[i];
	  
	  colors[index] = colorVal[i * 3 + 2];
	  vertices[index++] = depth[i];
	}
    }
}

void drawScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMultiDrawArrays(GL_TRIANGLE_FAN, first, count, 5);
  
  glFlush();
}

void setup(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  initializeArrays();
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glGenBuffers(1, buffer);

  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
  
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void*) sizeof(vertices));
}

void resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 1.0, 100.0, -1.0, 1.0);
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

int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
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
