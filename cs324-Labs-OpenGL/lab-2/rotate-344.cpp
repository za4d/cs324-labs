#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <stdlib.h>
#include <stddef.h>
#include <iostream>

void draw_stem()
{
	// in model cooridnates centred at (0,0)
	static float vertex[3][2] =
		{
			{-1.0f, -1.0f},
			{1.0f, -1.0f},
			{0.0f, 1.0f}
		};

	glBegin(GL_LINE_LOOP); 
	  glVertex2f(0.0f,0.0f);
	  glVertex2f(0.0f,1.0f);
	glEnd();
}

void fern_tree(float angle, int depth)
{
    if (depth > 1)
    {
      glPushMatrix();
	  
	  // translate it to where we want it
	  glTranslatef(0.0f, (1-(1/depth))*1.0f, 0.0f);
	  
	  // rotate anticlockwise in-plane by 60 degrees
	  glRotatef(angle, 0.0f, 0.0f, 1.0f); 
	  
	  // render primitives
	  draw_stem();
	  
	  //recursive call first
	  fern_tree(angle, depth-1);
	  
      glPopMatrix(); // done with stack

      glPushMatrix();
	  
	  // translate it to where we want it
	  glTranslatef(0.0f, (1-(1/depth))*1.0f, 0.0f);
	  
	  // rotate anticlockwise in-plane by 60 degrees
	  glRotatef(-angle, 0.0f, 0.0f, 1.0f); 
	  	  
	  // render primitives
	  draw_stem();
	  
	  //recursive call first
	  fern_tree(angle, depth-1);
	  
      glPopMatrix(); // done with stack
      
    }
  
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	
	glColor3f(1.0f, 1.0f, 1.0f); 

	glLineWidth(2.0f);
    
	float angle = 10.0f + drand48()*5;
	int depth = 10;
	
	// work on MODELVIEW matrix stack
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		// translate it to where we want it
		glTranslatef(500.0f, 500.0f, 0.0f);

		// scale it up 
		glScalef(25.0f, 25.0f, 1.0f);

		// render primitives
		draw_stem();
		
		fern_tree(angle, depth);
		
	glPopMatrix(); // done with stack

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
