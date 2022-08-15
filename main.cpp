#include <iostream>

#include <windows.h> // ������������ ���� ��� ������������� ������� Windows

#include <GL/glut.h>
#include <GL/freeglut.h>

float angle = 0.0f;

void changeSize(int w, int h) {
	// �������������� ������� �� ����
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// ���������� ������� ��������
	glMatrixMode(GL_PROJECTION);
	// �������� �������
	glLoadIdentity();
	// ���������� ��������� ��������
	glViewport(0, 0, w, h);
	// ���������� ���������� �����������
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// ��������� � ������� ��������
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	// ������� ������ ����� � �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��������� �������������
	glLoadIdentity();
	// ��������� ������
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0);
	glVertex3f(2.0f, -2.0f, 0.0);
	glEnd();

	angle += 0.1f;

	glutSwapBuffers();
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);

	//-------------Antialiasing----------
	//glEnable(GLUT_MULTISAMPLE);
	//glutSetOption(GLUT_MULTISAMPLE, 8);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH, GL_NICEST);

	//glEnable(GL_POINT_SMOOTH);
	//glHint(GL_POINT_SMOOTH, GL_NICEST);

	//------------Create window----------
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("���� 3");

	// �����������
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// ����� ������� ��� �����������
	glutIdleFunc(renderScene);

	// �������� ����
	glutMainLoop();

	return 0;
}