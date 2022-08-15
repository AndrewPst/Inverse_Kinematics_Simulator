#include <iostream>
#include <windows.h> // ������������ ���� ��� ������������� ������� Windows
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "WindowConfig.h"


//������� ���������� ��������� ���� ��� ���������������
void changeSize(int w, int h) {
	// �������������� ������� �� ����
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION); // ���������� ������� ��������
	glLoadIdentity(); // �������� �������
	glViewport(0, 0, w, h); // ���������� ��������� ��������
	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // ���������� ���������� �����������
	glMatrixMode(GL_MODELVIEW);// ��������� � ������� ��������
}


void renderScene(void) {
	// ������� ������ ����� � �������
	glClearColor(0.4, 0.4, 0.4,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��������� �������������
	glLoadIdentity();

	// ��������� ������
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0);
	glVertex3f(2.0f, -2.0f, 0.0);
	glEnd();


	glutSwapBuffers();
}

void init_openGL()
{
	//------Init parameters-----
	GLuint params = 0;
	params |= GLUT_DEPTH;
	params |= GLUT_DOUBLE;
	params |= GLUT_RGBA;
	//-----Use antialiasing----------
#ifdef _USE_MULTISAMPLE
	params |= GLUT_MULTISAMPLE;
	glEnable(GLUT_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, MULTISAMPLE_LEVEL);
#endif
	//---------Start openGL------------
	glutInitDisplayMode(params);
	glutInitWindowPosition(W_START_X, W_START_Y);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutCreateWindow(W_NAME);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	init_openGL();

	// �����������
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// ����� ������� ��� �����������
	glutIdleFunc(renderScene);

	// �������� ����
	glutMainLoop();

	return 0;
}