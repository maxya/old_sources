#include "afxwin.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glaux.h"

void myinit(void);
void CALLBACK display(void);
 
void myinit (void)
{
}

void CALLBACK display (void)
{
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
gluPerspective (130, 1, 50, 0);
glMatrixMode (GL_MODELVIEW);
glLoadIdentity ();
gluLookAt (150, 150, 150, 0, 0, 0, 0, 100, 0);
glColor3f(1,0,0);
glBegin(GL_LINE_LOOP);
glColor3f(1,0,0);
glVertex3f (0, 0, 0);
glVertex3f (200, 0, 0);
glEnd();
glBegin(GL_LINE_LOOP);
glColor3f(0,1,0);
glVertex3f (0, 0, 0);
glVertex3f (0, 200, 0);
glEnd();
glBegin(GL_LINE_LOOP);
glColor3f(0,0,1);
glVertex3f (0, 0, 0);
glVertex3f (0, 0, 200);
glEnd(); 
glFlush();
}

int main(int argc, char** argv)
{
auxInitDisplayMode (AUX_SINGLE | AUX_RGB);
auxInitPosition (0, 0, 500, 500);
auxInitWindow ("1-6");
myinit ();
auxMainLoop (display);
return(0);
}
