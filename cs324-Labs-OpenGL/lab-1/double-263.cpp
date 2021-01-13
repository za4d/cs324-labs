#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif
#include <cmath>
#include <iostream>

// redraw callback
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	
	// draw stuff -- into the backbuffer

	glColor3f(1.0f, 1.0f, 1.0f); // white

	float height = 1.0f; // height
	float width = 1.0f; // width
	
	// starting position
	float x = -1.0f; 
	float y = -1.0f; 
	float inc = 0.1f; 
	
	//increment
	
	
	const float steps = 2/inc; // how many steps once round the circle
	const float theta_step = 1; // angle step in radians

	
	
	glColor3f(1.0f, 1.0f, 1.0f); // white

	glBegin(GL_LINE_STRIP); // filled polygon
	// however many times once round the circle
	for (int i=0;i<=steps;i++) 
	{
		y = x*x*x;
		glVertex2f(x, y); 
		
		x += inc; 
		// debug to standard out
		std::cout << "x = " << x << ", y = " << y << std::endl;
	}
	glEnd();
	glBegin(GL_LINE_STRIP); // filled polygon
	// however many times once round the circle
	x = -1.0;
	for (int i=0;i<=steps;i++) 
	{
		y = sin(3*x);
		glVertex2f(x, y); 
		
		x += inc; 
		// debug to standard out
		std::cout << "x = " << x << ", y = " << y << std::endl;
	}
	glEnd();
	
	glutSwapBuffers(); // swap the backbuffer with the front
}

//
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	
	// set the GL display mode: double buffering and RGBA colour mode
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); // flags bitwise OR'd together
	
	glutInitWindowSize(512, 512); // window size
	glutInitWindowPosition(50, 50); // where on screen

	glutCreateWindow("Double Buffer"); 

	glutDisplayFunc(display); // set display callback

	glClearColor(0.0f, 1.0f, 0.0f, 0.0f); // clear colour -- green!
	
	glutMainLoop(); // go into the main loop and wait for window events...

	return 0; 
}
