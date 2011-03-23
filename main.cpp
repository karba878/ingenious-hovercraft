//
// main.cpp
//

#include "common.h"
#include "main.h"

//
// Step loop
//
void step()
{
   glutPostRedisplay();
}

//
// Main initialization
//
void init()
{
    // Initialize terrain
    t_init();

    // Initialize graphics
    g_init();
}

//
// Main loop
//
void timer(int i)
{
    step();
    glutTimerFunc(20, timer, i);
}

//
// Keyboard callbacks
//
void functionKeys(int key, int mouseX, int mouseY)
{
  switch (key)
    {
    case GLUT_KEY_F1: break;
   }
}
void keys(unsigned char key, int mouseX, int mouseY)
{
  switch (key)
    {
   }
}

//
// Main function
//
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
  
    init();

    // Register our display- and idle-functions with GLUT
    glutDisplayFunc(g_display);
    glutTimerFunc(20, timer, 0);
    glutSpecialFunc(functionKeys);
    glutKeyboardFunc(keys);

    // Enter GLUT's main loop; this function will never return
    glutMainLoop();

    return 0;
}
