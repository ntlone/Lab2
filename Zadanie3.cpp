#include "stdafx.h"
#include <GL\freeglut.h>

struct CVector{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

GLuint texture;

void GetNormal(CVector V1, CVector V2, CVector V3, CVector &N);
void RysujPiramide();

float rotX = 0.0f, rotY = 0.0f;
float color[3] = { 1.0f, 1.0f, 1.0f };
GLfloat whiteLight[4] = { 0.05f, 0.05f, 0.05f, 1.0f };
GLfloat sourceLight[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat lightPos[4] = { -10.f, 5.0f, 5.0f, 1.0f };


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
	RysujPiramide();

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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	char pixels[256 * 256];
	for (int x = 0; x < 256; x++)
	for (int y = 0; y < 256; y++)
		pixels[x * 256 + y] = rand() / 256;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 256, 256, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierwszy program w GLUT");

	SetupRenderingContext();

	glutKeyboardFunc(onKeyDown);
	glutReshapeFunc(onResize);
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

void RysujPiramide()
{
	CVector vertices[5] = {
		{  0.0f, 50.0f,  0.0f},
		{ -20.0f, 0.0f,  20.0f},
		{ -20.0f, 0.0f, -20.0f},
		{  20.0f, 0.0f, -20.0f },
		{  20.0f, 0.0f,  20.0f }
	};
	CVector normal;

	glBegin(GL_TRIANGLES);
	//Podstawa
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[3]);
	//Przednia sciana
	GetNormal(vertices[1], vertices[0], vertices[4], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[1]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	//Tylna sciana
	GetNormal(vertices[3], vertices[0], vertices[2], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[3]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	//Lewa sciana
	GetNormal(vertices[2], vertices[0], vertices[1], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[1]);
	//Prawa sciana
	GetNormal(vertices[4], vertices[0], vertices[3], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[3]);

	glEnd();
}

void GetNormal(CVector V1, CVector V2, CVector V3, CVector &N)
{
	V1.x = V1.x - V2.x;
	V1.y = V1.y - V2.y;
	V1.z = V1.z - V2.z;

	V2.x = V2.x - V3.x;
	V2.y = V2.y - V3.y;
	V2.z = V2.z - V3.z;
	
	N.x = V1.y * V2.z - V1.z * V2.y;
	N.y = V1.z * V2.x - V1.x * V2.z;
	N.z = V1.x * V2.y - V1.y * V2.x;
}