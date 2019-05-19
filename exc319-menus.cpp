//////////////////////////////////////////////////////////////////////////         
// menus.cpp
//
// This program shows an implementation of a pop-up menu (with a sub-menu) 
// using the GLUT library.
//
// Interaction:
// Press the right mouse button to see options.
//
// Sumanta Guha.
//////////////////////////////////////////////////////////////////////////

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

using namespace std;

#define FILLED 0
#define OUTLINED 1
#define LARGE 80
#define MEDIUM 60
#define SMALL 40


// Globals.
static float square_color[3] = {1.0, 0.0, 0.0}; // Color of the square.
static float width = MEDIUM, height = MEDIUM;
static int mode = FILLED;

// Drawing routine.
void drawScene(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

   glColor3fv(square_color);
   if (mode == FILLED) glBegin(GL_POLYGON);
   if (mode == OUTLINED) glBegin(GL_LINE_LOOP);
      glVertex3f(50 - width / 2, 50 - height / 2, 0.0);
      glVertex3f(50 + width / 2, 50 - height / 2, 0.0);
      glVertex3f(50 + width / 2, 50 + height / 2, 0.0);
      glVertex3f(50 - width / 2, 50 + height / 2, 0.0);
   glEnd();

   glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press the right mouse button to see options." << endl;  
}

// The top menu callback function.
void top_menu(int id)
{
   if (id==1) exit(0);
}

// The sub-menu callback function.
void color_menu(int id)
{
   if (id==2) 
   {
      square_color[0] = 1.0; square_color[1] = 0.0; square_color[2] = 0.0; 
   }
   if (id==3) 
   {
      square_color[0] = 0.0; square_color[1] = 0.0; square_color[2] = 1.0; 
   }
   glutPostRedisplay();
}

void mode_menu(int id)
{
  switch (id)
    {
    case 4:
      mode = FILLED;
      break;
    case 5:
      mode = OUTLINED;
      break;
    }
  glutPostRedisplay();
}
void width_menu(int id)
{
  switch (id)
    {
    case 6:
      width = SMALL;
      break;
    case 7:
      width = MEDIUM;
      break;
    case 8:
      width = LARGE;
      break;
    }
  glutPostRedisplay();
}
void height_menu(int id)
{
  switch (id)
    {
    case 9:
      height = SMALL;
      break;
    case 10:
      height = MEDIUM;
      break;
    case 11:
      height = LARGE;
      break;
    }
  glutPostRedisplay();
}
void size_menu(int id)
{
}


// Routine to make the menu.
void makeMenu(void)
{
   // The sub-menu is created first (because it should be visible when the top
   // menu is created): its callback function is registered and menu entries added.
  int colorMenu, modeMenu, sizeMenu, widthMenu, heightMenu;
   colorMenu = glutCreateMenu(color_menu);
   glutAddMenuEntry("Red", 2);
   glutAddMenuEntry("Blue", 3);

   modeMenu = glutCreateMenu(mode_menu);
   glutAddMenuEntry("Filled", 4);
   glutAddMenuEntry("Outlined", 5);

   widthMenu = glutCreateMenu(width_menu);
   glutAddMenuEntry("Small", 6);
   glutAddMenuEntry("Medium", 7);
   glutAddMenuEntry("Large", 8);

   heightMenu = glutCreateMenu(height_menu);
   glutAddMenuEntry("Small", 9);
   glutAddMenuEntry("Medium", 10);
   glutAddMenuEntry("Large", 11);

   sizeMenu = glutCreateMenu(size_menu);
   glutAddSubMenu("Width", widthMenu);
   glutAddSubMenu("Height", heightMenu);
   
   // The top menu is created: its callback function is registered and menu entries,
   // including a submenu, added.
   glutCreateMenu(top_menu);
   glutAddSubMenu("Color", colorMenu);
   glutAddSubMenu("Mode", modeMenu);
   glutAddSubMenu("Size", sizeMenu);
   glutAddMenuEntry("Quit",1);

   // The menu is attached to a mouse button.
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0);  

   // Make menu.
   makeMenu();
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
   glutCreateWindow("menus.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   
   glewExperimental = GL_TRUE; 
   glewInit(); 
   
   setup(); 

   glutMainLoop();
}
