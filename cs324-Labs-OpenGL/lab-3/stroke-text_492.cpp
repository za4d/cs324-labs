#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include <stddef.h>
#include <string.h>
#include <iostream>

int total_width = 0;
int get_text_length(const char* text)
{
  int total_width = 0;
  size_t len = strlen(text);
  for (size_t i=0 ;i<len;i++)
  {
    total_width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
  }
  return total_width;
}
void draw_text(const char* text)
{
	size_t len = strlen(text);
	for (size_t i=0;i<len;i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 

	glColor3f(1.0f, 1.0f, 1.0f); 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		total_width = get_text_length("Hello, World!");
		glTranslatef(500.0f-(total_width/2.0), 500.0f, 0.0f); // this will work
		glScalef(1.0f, 1.0f, 1.0f); // this will work
		draw_text("Hello, World!");
	glPopMatrix();

	glutSwapBuffers(); 
}

void keyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'q': exit(1); 
	}
	glutPostRedisplay(); 
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
	glutCreateWindow("Bitmap Text"); 
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard); 
	init(); 
	glutMainLoop(); 

	return 0; 
}
