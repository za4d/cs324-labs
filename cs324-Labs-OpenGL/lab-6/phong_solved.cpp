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

float mat_ambient_g = 0.05;
float mat_diffuse_g = 0.75;
float mat_specular_g = 1.00;
float mat_shininess_g = 50.0;
int shading = 0;
float x_value = 1.0;
float y_value = 1.0;
float z_value = 0.0;
void init();

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	
	// position and orient camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 0.5, 3, // eye position
			  0, 0, 0, // reference point
			  0, 1, 0  // up vector
		);

	// set the surface properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glutSolidTeapot(0.4);
	glutSwapBuffers(); 
}

void keyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'q': exit(1); break;

		case 'A': mat_ambient_g += 0.05; break;
		case 'a': mat_ambient_g -= 0.05; break;
		case 'D': mat_diffuse_g += 0.05; break;
		case 'd': mat_diffuse_g -= 0.05; break;
		case 'S': mat_specular_g += 0.05; break;
		case 's': mat_specular_g -= 0.05; break;
		case 'E': mat_shininess_g += 5; break;
		case 'e': mat_shininess_g -= 5; break;
		case 'T': shading = 0; init(); break;
		case 't': shading = 1; init(); break;
		case 'X': x_value += 0.5; init(); break;
		case 'x': x_value -= 0.5; init(); break;
		case 'Y': y_value += 0.5; init(); break;
		case 'y': y_value -= 0.5; init(); break;
		case 'Z': z_value += 0.5; init(); break;
		case 'z': z_value -= 0.5; init(); break;
		
	}
	mat_ambient[0] = mat_ambient_g;mat_ambient[1] = mat_ambient_g; mat_ambient[2] = mat_ambient_g;
	mat_diffuse[0] = mat_diffuse_g;mat_diffuse[1] = mat_diffuse_g; mat_diffuse[2] = mat_diffuse_g;
	mat_specular[0] = mat_specular_g;mat_specular[1] = mat_specular_g; mat_specular[2] = mat_specular_g;
	mat_shininess[0] = mat_shininess_g;
	
	std::cout<<"ambient"<<mat_ambient_g<<"   ";
	std::cout<<"diffuse"<<mat_diffuse_g<<"   ";
	std::cout<<"specular"<<mat_specular_g<<"   ";
	std::cout<<"shininess"<<mat_shininess_g<<std::endl;
	init();
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
	float light_ambient[] = {0.1, 0.1, 0.1, 1.0};
	float light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	// fix the light position
	float light_position[] = {x_value, y_value, z_value, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// enable lighting and turn on the light0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// so that hidden surfaces are removed
	glEnable(GL_DEPTH_TEST);

	// mode of shading
	if (shading == 0)
	  glShadeModel(GL_FLAT);
	else
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
