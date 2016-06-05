#include "stdafx.h"
#include <GL\freeglut.h>
#include <cmath>

void RysujKorkociag(int n);

float rotX = 0.0f, rotY = 0.0f;
float color[3] = { 1.0f, 0.0f, 0.0f };

void Display()
{
	//15 - k¹t

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3fv(color);
	RysujKorkociag(15);

	glutSwapBuffers();
}

void onResize(int w, int h)
{
	if (h == 0)
		h = 1;

	float aspect = (float)w / (float)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		glOrtho(-100.0f, 100.0, -100.0f / aspect, 100.0 / aspect, 100.0f, -100.0f);
	}
	else
	{
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0f, 100.0, 100.0f, -100.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SetupRenderingContext()
{
	glClearColor(0.5f, 0.35f, 0.05f, 1.0f);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}

void onKeyDown(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		rotX += 5.0f;

	if (key == GLUT_KEY_DOWN)
		rotX -= 5.0f;

	if (key == GLUT_KEY_LEFT)
		rotY -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		rotY += 5.0f;

	glutPostRedisplay();
}

void Menu(int value)
{
	switch (value)
	{
	case 1:
		color[0] = 1.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		break;
	case 2:
		color[0] = 0.0f;
		color[1] = 1.0f;
		color[2] = 0.0f;
		break;
	case 3:
		color[0] = 0.0f;
		color[1] = 0.0f;
		color[2] = 1.0f;
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierwszy program w GLUT");

	SetupRenderingContext();

	glutCreateMenu(Menu);
	glutAddMenuEntry("Kolor czerwony.", 1);
	glutAddMenuEntry("Kolor zielony.", 2);
	glutAddMenuEntry("Kolor niebieski.", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutKeyboardFunc(onKeyDown);
	glutReshapeFunc(onResize);
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

void RysujKorkociag(int n)
{
	GLfloat z = 0.0f;
	GLfloat x, y;
	GLfloat pointSize = 1.0f;

	for (float i = 0; i < (2*3.1415f) * n; i += 0.3f)
	{

		x = 10 * sin(i);
		y = 10 * cos(i);
		z += 0.3;

		glPointSize(pointSize += 0.01);

		glBegin(GL_POINTS);
		glVertex3f(x, y, z);
		glEnd();
	}

}