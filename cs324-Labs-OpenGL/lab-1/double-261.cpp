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

	const float radius = 0.5f; // a given radius
	const float pi = atan(1)*4; // define pi

	const size_t steps = 32; // how many steps once round the circle
	const float theta_step = 2*pi/float(steps); // angle step in radians

	float theta = 0.0f;

	glColor3f(1.0f, 1.0f, 1.0f); // white

	glBegin(GL_POLYGON); // filled polygon
	// however many times once round the circle
	for (size_t i=0;i<steps;i++, theta+=theta_step) 
	{
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		glVertex2f(x, y); 
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
