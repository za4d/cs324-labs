#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <iostream>

#include <stdlib.h>
#include <stddef.h>

#include "draw_text.h"
#include "lights_material.h"

float g_eye_z = 2.0f;
bool is_lighting = false; // toggle

void draw_triangle()
{
	// in model cooridnates centred at (0,0)
	static float vertex[3][3] =
		{
			{-1.0f, -1.0f, 0.0f},
			{1.0f, -1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f}
		};

	glBegin(GL_LINE_LOOP); 
		for (size_t i=0;i<3;i++)
			glVertex3fv(vertex[i]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	
	// position and orient camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, g_eye_z, // eye position
			  0, 0, 0, // reference point
			  0, 1, 0  // up vector
		);

	glColor3f(1.0f, 1.0f, 1.0f); 

	if (!is_lighting)
	{
		glDisable(GL_LIGHTING);
		draw_triangle();  
		glEnable(GL_LIGHTING);
	}
	else
		draw_triangle();

	glDisable(GL_LIGHTING);
		// put some help on the screen
		draw_text(20, 20, "Use 'z'/'Z' to change eye Z position");
	glEnable(GL_LIGHTING);


	glutSwapBuffers(); 
}

void keyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'q': exit(1); break;
		case 'z': g_eye_z += 0.5f; break;
		case 'Z': g_eye_z -= 0.5f; break;

		case 't': is_lighting = !is_lighting; break;
	}
	std::cerr << "\t eye z  = " << g_eye_z << std::endl;

	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	// for perspective projection use the GLU helper
	// take FOV, ASPECT RATIO, NEAR, FAR 
	gluPerspective(40.0, 1.0f, 1.0, 5.0);
}

void init()
{
	init_lights();
	init_material();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH); 
	
	glutInitWindowSize(512, 512); 
	glutInitWindowPosition(50, 50); 

	glutCreateWindow("Perspective Viewing"); 

	glutKeyboardFunc(keyboard); 
	glutReshapeFunc(reshape); 
	glutDisplayFunc(display); 

	init(); 

	glutMainLoop(); 

	return 0; 
}
