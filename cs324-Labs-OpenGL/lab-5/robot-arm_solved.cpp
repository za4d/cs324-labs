#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <iostream>

#include <stdlib.h>
#include <stddef.h>

#include "capped_cylinder.h"
#include "lights_material.h"
#include "draw_text.h"

bool g_draw_teapot = false; // toggle

enum robot_parts_t {
			SHOULDER=0, ARM=1, FOREARM=2, 
			HAND=3, NUM_PARTS=4
		};

// these will be display list base for all cylinders
size_t g_robot = 0;

const float g_shoulder_height = 0.2f;
const float g_arm_length = 0.6f;
const float g_forearm_length = 0.4f;
const float g_hand_thickness = 0.075f;

// rotation angles of arm
float g_theta = 0.0f;
float g_phi = 0.0f;
float g_elbow_angle = 0.0f;
float g_wrist_angle = 0.0f;
float g_hand_angle = 0.0f;

void make_robot_arm()
{
	g_robot = glGenLists(NUM_PARTS);
	
	// compile display list for shoulder
	glNewList(g_robot + SHOULDER, GL_COMPILE);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			capped_cylinder(0.2f, g_shoulder_height);
		glPopMatrix();
	glEndList();

	glNewList(g_robot + ARM, GL_COMPILE);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			capped_cylinder(0.1f, g_arm_length);
		glPopMatrix();
	glEndList();

	glNewList(g_robot + FOREARM, GL_COMPILE);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			capped_cylinder(0.065f, g_forearm_length);
		glPopMatrix();
	glEndList();

	glNewList(g_robot + HAND, GL_COMPILE);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			capped_cylinder(0.1f, g_hand_thickness);
		glPopMatrix();

		// finger
		glPushMatrix();
			glTranslatef(-0.06, 0.0f, 0.0f);
			glRotatef(-90, 1, 0, 0);
			capped_cylinder(0.025f, 0.2f);
		glPopMatrix();

		// thumb
		glPushMatrix();
			glTranslatef(0.06, 0.0f, 0.0f);
			glRotatef(-90, 1, 0, 0);
			capped_cylinder(0.025f, 0.2f);
		glPopMatrix();

	glEndList();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

	// position and orient camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 3.0, 1.5, // eye position
			  0, 0, -0.5, // reference point
			  0, 1, 0  // up vector
		);

	// draw a ground plane square for reference
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 1.0f); 
	glBegin(GL_LINE_LOOP);
		glVertex3f(-0.5f, 0.0f, 0.5f);
		glVertex3f(0.5f, 0.0f, 0.5f);
		glVertex3f(0.5f, 0.0f, -0.5f);
		glVertex3f(-0.5f, 0.0f, -0.5f);
	glEnd();
	glEnable(GL_LIGHTING);

	// draw the arm parts and articulate them
	glPushMatrix();

		// place the shoulder at origin (this is the default)
		glTranslatef(0.0f, 0.0f, 0.0f);

		// draw shoulder
		glCallList(g_robot + SHOULDER);

		// move to top of shoulder using g_shoulder_height 
		glTranslatef(0.0f, g_shoulder_height, 0.0f);

		glPushMatrix();

			// get ready to apply the arm rotations
			glRotatef(g_phi, 0, 1, 0); 
			glRotatef(g_theta, 1, 0, 0);

			// draw the arm
			glCallList(g_robot + ARM);

			// move to end of arm
			glTranslatef(0.0f, g_arm_length, 0.0f);

			glPushMatrix();

				// get ready to apply the arm rotations
				glRotatef(g_elbow_angle, 1, 0, 0); 
				//glRotatef(g_theta, 1, 0, 0);

				// draw the arm
				glCallList(g_robot + FOREARM);

				// move to end of arm
				glTranslatef(0.0f, g_forearm_length, 0.0f);


				// connect hand
				glPushMatrix();

					// set the wriat angle and hand angles
					glRotatef(g_wrist_angle, 1, 0, 0);
					glRotatef(g_hand_angle, 0, 1, 0);

					// draw the hand
					glCallList(g_robot + HAND);
					
					// move to end of forearm
					glTranslatef(0.0f, g_hand_thickness, 0.0f);

				glPopMatrix();

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();

	// fast-key help on the screen
    glDisable(GL_LIGHTING);
        // put some help on the screen
        draw_text(20, 960, "Use 't'/'T' to change theta angle");
        draw_text(20, 920, "Use 'p'/'P' to change phi angle");
	draw_text(20, 880, "Use 'e'/'E' to change Elbow angle");
	draw_text(20, 840, "Use 'w'/'W' to change Wrist angle");
	draw_text(20, 800, "Use 'h'/'H' to change Hand angle");
    glEnable(GL_LIGHTING);

	
	glutSwapBuffers(); 
}

void keyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'q': exit(1); break;

		case 't': g_theta += 5.0f; break;
		case 'T': g_theta -= 5.0f; break;
		case 'p': g_phi += 5.0f; break;
		case 'P': g_phi -= 5.0f; break;
		case 'e': g_elbow_angle += 5.0f; break;
		case 'E': g_elbow_angle -= 5.0f; break;
		case 'w': g_wrist_angle += 5.0f; break;
		case 'W': g_wrist_angle -= 5.0f; break;
		case 'h': g_hand_angle += 5.0f; break;
		case 'H': g_hand_angle -= 5.0f; break;
	}
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
	// magic invocations...ohmmm
	init_lights();
	init_material();

	// compile display lists for the parts
	make_robot_arm();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH); 
	glutInitWindowSize(512, 512); 
	glutInitWindowPosition(50, 50); 

	glutCreateWindow("Robot Arm"); 

	glutKeyboardFunc(keyboard); 
	glutReshapeFunc(reshape); 
	glutDisplayFunc(display); 

	init(); 

	glutMainLoop(); 

	return 0; 
}
