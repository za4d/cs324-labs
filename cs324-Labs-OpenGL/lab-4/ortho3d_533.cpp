#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <iostream>
#include "draw_text.h"
#include <stdlib.h>
#include <stddef.h>

size_t g_the_cube = 0;
float g_eye_x = 0.0f;
float g_eye_y = 0.0f;
float g_eye_z = 2.0f;
float near_plane = -4.0f;
void init();
size_t make_cube()
{
	static float vertices[8][3] = 
		{
			{-0.5f, -0.5f, -0.5f}, // front
			{0.5f, -0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{-0.5f, 0.5f, -0.5f},
			{-0.5f, -0.5f, 0.5f}, // back 
			{0.5f, -0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f}
		};

	// indices into verices
	static size_t faces[6][4] =
		{
			{0, 1, 2, 3},  // front
			{5, 4, 7, 6},  // back
			{4, 0, 3, 7},  // left
			{1, 5, 6, 2},  // right
			{4, 5, 1, 0},  // bottom
			{3, 2, 6, 7}   // top
		};

	// compile into a display list
	size_t handle = glGenLists(1);

	glNewList(handle, GL_COMPILE);
	glBegin(GL_QUADS);
	for (size_t f=0;f<6;f++) // for each face
	for (size_t v=0;v<4;v++) 
		glVertex3fv(vertices[faces[f][v]]);
	glEnd();
	glEndList();

	return handle;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	
	// position and orient camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_eye_x, g_eye_y, g_eye_z, // eye position
			  0, 0, 0, // reference point
			  0, 1, 0  // up vector
		);

	// draw something in 3D
	glColor3f(1.0f, 1.0f, 1.0f); 
	glCallList(g_the_cube);
	draw_text(20, 20, "Use 'z'/'Z' to change eye Z position");
	draw_text(20, 50, "Use 'y'/'Y' to change eye Y position");
	draw_text(20, 80, "Use 'x'/'X' to change eye X position");
	draw_text(20, 110, "Use 'n'/'N' to change near plane position");
	glutSwapBuffers(); 
}

void keyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'q': exit(1); break;
		case 'z': g_eye_z += 0.5f; break;
		case 'Z': g_eye_z -= 0.5f; break;
		case 'x': g_eye_x += 0.5f; break;
		case 'X': g_eye_x -= 0.5f; break;
		case 'y': g_eye_y += 0.5f; break;
		case 'Y': g_eye_y -= 0.5f; break;
		case 'n': near_plane += 1.0f; break;
		case 'N': near_plane -= 1.0f; break;
	}
	std::cerr << "\t eye z  = " << g_eye_z << std::endl;
	std::cerr << "\t eye y  = " << g_eye_y << std::endl;
	std::cerr << "\t eye x  = " << g_eye_x << std::endl;
	std::cerr << "\t eye n  = " << near_plane << std::endl;
	init();
	glutPostRedisplay();
}

void init()
{
	// set orthographic viewing
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	// specify a projection with 
	//    this view volume, centred on origin 
	// takes LEFT, RIGHT, BOTTOM, TOP, NEAR and FAR
	glOrtho(-2.0, 2.0, -2.0, 2.0, near_plane, 4.0);

	g_the_cube = make_cube();

	// draw stuff as wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); 
	glutInitWindowSize(512, 512); 
	glutInitWindowPosition(50, 50); 

	glutCreateWindow("Orthographic Viewing");
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display); 
	init(); 
	glutMainLoop(); 

	return 0; 
}
