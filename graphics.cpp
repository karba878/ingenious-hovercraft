//
// graphics.cpp
//

#include "common.h"
#include "graphics.h"

//
// Initialize graphics
//
void g_init()
{
    // Configure GLUT:
    //  - framebuffer with RGB + Alpha values per pixel
    //  - Z-buffer
    //  - two sets of above mentioned buffers, so that
    //    doublebuffering is possible
    //
    // Initial window size 800x800
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 640);
    glutCreateWindow("Ingenious Hovercraft - The last Voyage");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.01, 1000);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0, 0.5, -0.5);
    //glRotatef(0, 1, 0, 0);
    //glRotatef(0, 0, 1, 0);
    //getMatrix();
}

//
// Main display function
//
void g_display()
{
    // This function is called whenever it is time to render
    // a new frame; due to the idle()-function below, this
    // function will get called several times per second
  
    // Clear framebuffer & zbuffer
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render terrain
    g_display_terrain();

    // Swap front- and backbuffers
    glutSwapBuffers();
}

//
// Display terrain
//
void g_display_terrain()
{

    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);

    // Loop all segments in terrain, render from previous segment to current
    for(int s=1; s<T_BUFFER_LENGTH; s++) // Note! s=1
    {
        int cur_seg_index  = t_terrain_sta + s;
        int last_seg_index = t_terrain_sta + s - 1;
        if(cur_seg_index  >= T_BUFFER_LENGTH) cur_seg_index  -= T_BUFFER_LENGTH;
        if(last_seg_index >= T_BUFFER_LENGTH) last_seg_index -= T_BUFFER_LENGTH;
        if(cur_seg_index == t_terrain_end)
            break;

        terrain_seg* cur_seg  = &(t_terrain[cur_seg_index]);
        terrain_seg* last_seg = &(t_terrain[last_seg_index]);

        double zc  = T_TERRAIN_SEG_DIST*s;    // Current z
        double zl = T_TERRAIN_SEG_DIST*(s-1); // Last z

        for(int d=0; d<(T_TERRAIN_DOT_N-2); d+=2)
        {
            double xc1,xc2,xc3,xl1,xl2,xl3;
            double yc1,yc2,yc3,yl1,yl2,yl3;

            xc1 = cur_seg->dots[d  ].x;
	    xc2 = cur_seg->dots[d+1].x;
            xc3 = cur_seg->dots[d+2].x;

            xl1 = last_seg->dots[d  ].x;
	    xl2 = last_seg->dots[d+1].x;
            xl3 = last_seg->dots[d+2].x;

            yc1 = cur_seg->dots[d  ].y;
	    yc2 = cur_seg->dots[d+1].y;
            yc3 = cur_seg->dots[d+2].y;

            yl1 = last_seg->dots[d  ].y;
	    yl2 = last_seg->dots[d+1].y;
            yl3 = last_seg->dots[d+2].y;

            // Top-left triangle
            glVertex3f(xl1,yl1,zl);
            glVertex3f(xc2,yc2,zc);
            glVertex3f(xc1,yc1,zc);

            // Bottom-left triangle
            glVertex3f(xl1,yl1,zl);
            glVertex3f(xl2,yl2,zl);
            glVertex3f(xc2,yc2,zc);

            // Bottom-right triangle
            glVertex3f(xc2,yc2,zc);
            glVertex3f(xl2,yl2,zl);
            glVertex3f(xl3,yl3,zl);

            // Top-right triangle
            glVertex3f(xl3,yl3,zl);
            glVertex3f(xc3,yc3,zc);
            glVertex3f(xc2,yc2,zc);
        }

    }

    glEnd();

    glPopAttrib();
    glPopMatrix();
}
