#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <stdlib.h>
#include <stddef.h>

void draw_triangle()
{
	// in model cooridnates centred at (0,0)
	static float vertex[3][2] =
		{
			{-1.0f, -1.0f},
			{1.0f, -1.0f},
			{0.0f, 1.0f}
		};

	glBegin(GL_LINE_LOOP); 
		for (size_t i=0;i<3;i++)
			glVertex2fv(vertex[i]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	
	glColor3f(1.0f, 1.0f, 1.0f); 

	glLineWidth(2.0f);

	// work on MODELVIEW matrix stack
	glMatrixMode(GL_MODELVIEW);
	for (int i=0;i<5;i++){
	  double x = (drand48()-0.5)*500;
	  double y = (drand48()-0.5)*500;
	  double angle = drand48()*360;
	  glPushMatrix();

		  // translate it to where we want it
		  glTranslatef(x+500, y+500, 0.0f);

		  // scale it up 
		  glScalef(50.0f, 50.0f, 1.0f);

		  // rotate anticlockwise in-plane by 60 degrees
		  glRotatef(angle, 0.0f, 0.0f, 1.0f); 


		  // render primitives
		  draw_triangle();

	  glPopMatrix(); // done with stack
	}
	glutSwapBuffers(); 
}

void init()
{
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f); 
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); 
	glutInitWindowSize(512, 512); 
	glutInitWindowPosition(50, 50); 
	glutCreateWindow("Rotate"); 
	glutDisplayFunc(display); 

	init(); 
	glutMainLoop(); 

	return 0; 
}
