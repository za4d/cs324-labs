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
	float x0 = -0.5f; 
	float y0 = -0.5f; 
	
	//increment
	
	
	const size_t steps = 8; // how many steps once round the circle
	const float theta_step = 1; // angle step in radians

	
	float inc = height/(2*steps); 
	
	glColor3f(1.0f, 1.0f, 1.0f); // white

	glBegin(GL_LINE_STRIP); // filled polygon
	// however many times once round the circle
	for (size_t i=0;i<steps;i++) 
	{
		glVertex2f(x0, y0); 
		
		glVertex2f(x0+height, y0); 
		glVertex2f(x0+height, y0+width);
		x0 += inc; 
		height -= inc*2;
		
		glVertex2f(x0, y0+width);
		y0 += inc;
		width -= inc*2;
		// debug to standard out
		std::cout << "height = " << height << ", width = " << width << std::endl;
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
