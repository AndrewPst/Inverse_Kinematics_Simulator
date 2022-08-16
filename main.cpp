#include <iostream>
#include <windows.h> // Заголовочный файл для использования функций Windows
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "WindowConfig.h"

#define _USE_MATH_DEFINES
#include <math.h>

//Функция сохранения пропорций окна при масштабировании
void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION); // используем матрицу проекции
	glLoadIdentity(); // обнуляем матрицу
	glViewport(0, 0, w, h); // установить параметры вьюпорта
	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // установить корректную перспективу
	glMatrixMode(GL_MODELVIEW);// вернуться к матрице проекции
}

constexpr float CAMERA_SPEED = 0.02;

float camera_speed_l = 0;
float camera_pos_l = 5.f;

void pressKey(int key, int xx, int yy)
{
	switch (key) {
	case GLUT_KEY_UP:
		camera_speed_l = -CAMERA_SPEED;
		break;
	case GLUT_KEY_DOWN:
		camera_speed_l = CAMERA_SPEED;
		break;
	}
}

void releaseKey(int key, int xx, int yy)
{
	switch (key) {
	case GLUT_KEY_UP:
		camera_speed_l = 0;
		break;
	case GLUT_KEY_DOWN:
		camera_speed_l = 0;
		break;
	}
}


float angle_y = M_PI ;
float angle_x = 0;
int xOrigin = -1, yOrigin = -1;

void mauseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP) {
			xOrigin = -1;
			yOrigin = -1;
		}
		else {
			xOrigin = x;
			yOrigin = y;
		}
	}
}

void mauseMoveButton(int x, int y)
{
	if (xOrigin >= 0) {

		// update deltaAngle
		angle_y += (x - xOrigin) * 0.005f;
		xOrigin = x;
	}
	if (yOrigin >= 0) {
		angle_x += (y - yOrigin) * 0.005f;
		yOrigin = y;
	}
}


void setupCamera()
{
	camera_pos_l += camera_speed_l;
	float _x = 0, _z = -camera_pos_l, _y = 0;
	float _nx, _ny, _nz;
	_ny = _y * cos(angle_x) - _z * sin(angle_x);
	_nz = _y * sin(angle_x) + _z * cos(angle_x);

	_nx = _x * cos(angle_y) - _nz * sin(angle_y);
	_nz = _x * sin(angle_y) + _nz * cos(angle_y);

	// установка камеры
	gluLookAt(_nx, _ny, _nz,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
}



GLfloat vert[] = {
	0, 0, 1,
	0, 1, 1,
	1, 1, 1,
	1, 0, 1,
	0, 0, 0,
	0, 1, 0,
	1, 1, 0,
	1, 0, 0
};

GLfloat colors[] = {
	0, 0, 1,
	0, 1, 0,
	0, 1, 1,
	1, 0, 0,
	1, 0, 1,
	1, 1, 0,
	1, 1, 1,
	0, 0, 0
};

GLushort ind[] = {
	0, 3, 2, 1,
	0, 1, 5, 4,
	7, 4, 5, 6,
	3, 7, 6, 2,
	1, 2, 6, 5,
	0, 4, 7, 3
};

double anim_c = 0;

void renderScene(void) {
	// очистка буфера цвета и глубины
	glClearColor(0.4, 0.4, 0.4, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// обнуление трансформации
	glLoadIdentity();
	setupCamera();


	//---draw 1 cube-----
	glPushMatrix();

	glRotatef(anim_c, 0, 0, 1);
	glTranslatef(-2, 0, 0);
	glRotatef(-anim_c, 0, 0, 1);
	glRotatef(-sin(anim_c*0.01)*180/M_PI*10, 1, 1, 1);
	glTranslatef(-0.5, -0.5, -0.5);


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vert);

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glEnableClientState(GL_INDEX_ARRAY);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, ind);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glPopMatrix();

	//-----draw 2 cube--------
	glPushMatrix();
	//glRotatef(-anim_c, 0, 1, 0);
	glTranslatef(-0.5, -0.5, -0.5);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vert);

	glColor3f(0.5, 0.5, 0.5);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glEnableClientState(GL_INDEX_ARRAY);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, ind);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glPopMatrix();

	anim_c += 1;

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
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glEnable(GL_CULL_FACE);

	setupCamera();
}

void registerGlcallbacks()
{
	// регистрация
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(pressKey);

	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	glutMouseFunc(mauseButton);
	glutMotionFunc(mauseMoveButton);

	glutIdleFunc(renderScene);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	init_openGL();
	registerGlcallbacks();


	// основной цикл
	glutMainLoop();

	return 0;
}