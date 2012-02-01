///Laba *.* 
///Maxim Gorbanev
#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glaux.lib")

#define ROTATE_SPEED	4.0
#define WIDTH	600
#define HEIGHT  600

static int time = 0; 
int alpha = 0;
int beta = 0;
void CALLBACK oGl_Render(void);

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////Draw Primitivs//////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void DrawPrimitivs(void)
{
	//Draw triangle!
	glPushMatrix();
		glLoadIdentity();
		glRotated(180,0,1,0);
		glRotated(30,1,0,0);
		glTranslated(2,1,0);
		glBegin(GL_TRIANGLES);
			glColor3d(1,0,0);
			glVertex3d(0,0,0);		
			glColor3d(0,1,0);
			glVertex3d(-2,3,0);
			glColor3d(0,0,1);
			glVertex3d(2,4,0);
		glEnd();
	glPopMatrix();

//Draw small teapot
  	glPushMatrix();
		glLoadIdentity();
		glTranslated(3,3,-5);
		glRotated(time,1.,1.,1.);
		glColor3d(0,1,0);
		auxSolidTeapot(1);
		time++;
	glPopMatrix();
//Draw small box		
	glPushMatrix();
		glLoadIdentity();
		glTranslated(3,-3,-5);
		glRotated(time,1.,1.,1.);
		glColor3d(0,0,1);
		auxSolidBox(2,2,2);		
	glPopMatrix();
}
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Draw Stakan!/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void Stakan(void)
{
	GLUquadricObj *quarObj;
	quarObj = gluNewQuadric();
	
	glPushMatrix();
	  glColor3d(1,0,0);
	  glTranslated(0,-1,0);
	  glRotated(-90,1,0,0);
	  
	  gluQuadricDrawStyle(quarObj,GLU_FILL);	  	  
	  gluCylinder(quarObj,0.77,1,2.30,16,1);
	  
	  glPushMatrix();
	    glRotated(180,1,0,0);
	    gluDisk(quarObj,0,0.77,16,1);		
	  glPopMatrix();

    glPopMatrix();

	gluDeleteQuadric(quarObj);	
}

//Key Callback Funktions
void CALLBACK Proc_Left(void)
{	
	glRotated(ROTATE_SPEED,0,1,0);	
	oGl_Render();
}

void CALLBACK Proc_Right(void)
{
	glRotated(-ROTATE_SPEED,0,1,0);
	oGl_Render();
}

void CALLBACK Proc_Up(void)
{
	glRotated(ROTATE_SPEED,0,0,1);
	oGl_Render();
}

void CALLBACK Proc_Down(void)
{
	glRotated(-ROTATE_SPEED,0,0,1);
	oGl_Render();	
}

void CALLBACK Proc_Quit(void)
{
	PostQuitMessage(0);
}

//Mouse Proc
void CALLBACK Mouse_Proc(AUX_EVENTREC *event)
{	
	static int x0, y0 = -12345; 

	if(y0!=-12345)
	{
		alpha += event->data[AUX_MOUSEX] - x0;
		beta += event->data[AUX_MOUSEY] - y0;
	}
	x0 = event->data[AUX_MOUSEX];
	y0 = event->data[AUX_MOUSEY];
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////Main Render Function////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void CALLBACK oGl_Render(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
		//Mouse movement!
		glRotated(alpha, 0,1,0);
		glRotated(beta, -1,0,0);

		//DrawPrimitivs();
		Stakan();
		//Large Teapot			
		
		//glColor3d(1,0,1);		
		//auxWireTeapot(2);
			
	glPopMatrix();

	auxSwapBuffers();		
}

void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5,3,15);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////MAIN ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
float pos[4] = {1,1,10,1};
float dir[3] = {-1,-1,-1};
float lposSt[4] = {0,0,0,1};
float dir2[3] = {1,1,1};
int val = 180;

    GLfloat mat_specular[] = {3,3,3,10};

    auxInitPosition( 250, 110, WIDTH, HEIGHT);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH24 | AUX_DOUBLE);    
	auxInitWindow("OpenGL Laba Project!");
    auxIdleFunc(oGl_Render);
    auxReshapeFunc(resize);	
    
	glEnable(GL_DEPTH_TEST);	
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_FLAT);
	
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);	

	glLightfv(GL_LIGHT1, GL_POSITION, lposSt);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir2);
	glLightiv(GL_LIGHT1, GL_SPOT_CUTOFF, &val);



    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);    
	
	auxKeyFunc(AUX_LEFT, Proc_Left);
	auxKeyFunc(AUX_RIGHT, Proc_Right);
	auxKeyFunc(AUX_UP, Proc_Up);
	auxKeyFunc(AUX_DOWN, Proc_Down);	
	auxKeyFunc(AUX_ESCAPE, Proc_Quit);	
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSELOC, Mouse_Proc);	

    auxMainLoop(oGl_Render);
	return 0;
}
