#include "stdafx.h"
#include <GL\freeglut.h>

void RysujStozek();

float rotX = 0.0f, rotY = 0.0f;

void Display()
{
	//15 - k¹t

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	RysujStozek();

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
		glShadeModel(GL_FLAT);
		break;
	case 2:
		glShadeModel(GL_SMOOTH);
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
	glutAddMenuEntry("Cieniowanie plaskie.", 1);
	glutAddMenuEntry("Cieniowanie Gourauda.", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutKeyboardFunc(onKeyDown);
	glutReshapeFunc(onResize);
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

void RysujStozek()
{
	glBegin(GL_TRIANGLE_FAN);

	//Podstawa
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-22.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-20.0f, 8.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-17.0f, 15.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-10.0f, 20.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 22.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(10.0f, 20.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(17.0f, 15.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(20.0f, 8.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(22.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(20.0f, -8.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(17.0f, -15.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(10.0f, -20.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-10.0f, -20.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-17.0f, -15.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-20.0f, -8.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-22.0f, 0.0f);

	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	//Stozek
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -50.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-22.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-20.0f, 8.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-17.0f, 15.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-10.0f, 20.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 22.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(10.0f, 20.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(17.0f, 15.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(20.0f, 8.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(22.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(20.0f, -8.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(17.0f, -15.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(10.0f, -20.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-10.0f, -20.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-17.0f, -15.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-20.0f, -8.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-22.0f, 0.0f);

	glEnd();
}