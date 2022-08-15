#include <iostream>

#include <windows.h> // Заголовочный файл для использования функций Windows

#include <GL/glut.h>
#include <GL/freeglut.h>

float angle = 0.0f;

void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	// очистка буфера цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнуление трансформации
	glLoadIdentity();
	// установка камеры
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
	glutCreateWindow("Урок 3");

	// регистрация
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// новая функция для регистрации
	glutIdleFunc(renderScene);

	// основной цикл
	glutMainLoop();

	return 0;
}