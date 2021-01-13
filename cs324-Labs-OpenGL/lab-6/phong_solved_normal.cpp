#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <iostream>

#include <stdlib.h>
#include <stddef.h>

// properties of some material
float mat_ambient[] = {0.05, 0.05, 0.05, 1.0};
float mat_diffuse[] = {0.75, 0.75, 0.75, 1.0};
float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
float mat_shininess[] = {50.0};

void cross_product(const float* v1, const float* v2, float* v3)
{
    v3[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    v3[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    v3[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
}

void draw_triangle()
{
	
	// // in model cooridnates centred at (0,0)
	const float vertex[3][3] =
		{
			{-1.0f, -1.0f, 0.0f},
			{1.0f, -1.0f, 0.0f},
			{0.0f, 1.0f, 0.0f}
		};

	// glColor3f(0.0f, 0.0f, 1.0f);

	float normal[3]; 

    cross_product(vertex[0],vertex[1],normal);
    glNormal3f ( normal[0], normal[1] , normal[2] );

	glBegin(GL_TRIANGLES); 
		for (size_t i=0;i<3;i++)
		{
			glVertex3fv(vertex[i]);
		}
	glEnd();
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	
	// position and orient camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, // eye position
			  0, 0, 0, // reference point
			  0, 1, 0  // up vector
		);

	// set the surface properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// glutSolidTeapot(0.4);
    draw_triangle();


	glutSwapBuffers(); 
}

void keyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'q': exit(1); break;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(40.0, 1.0f, 1.0, 5.0);

	glutPostRedisplay();
}

void init()
{
	// we can do this once if we don't intend to change the light properties
	// incident energy properties of a light
	float light_ambient[] = {1.0, 0.0, 0.0, 1.0};
	float light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
	float light_specular[] = {1.0, 0.0, 0.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	// fix the light position
	float light_position[] = {1.0, 1.0, 2.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// enable lighting and turn on the light0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// so that hidden surfaces are removed
	glEnable(GL_DEPTH_TEST);

	// mode of shading
	glShadeModel(GL_SMOOTH); // can be GL_FLAT, GL_SMOOTH
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH); 

	glutInitWindowSize(512, 512); 
	glutInitWindowPosition(50, 50); 

	glutCreateWindow("Phong"); 

	glutKeyboardFunc(keyboard); 
	glutReshapeFunc(reshape); 
	glutDisplayFunc(display); 

	init(); 

	glutMainLoop(); 

	return 0; 
}
