#include "pch.h"
#include "framework.h"
#include "shader.h"
#define TIMERCLOCK 13


CFramework framework;

GLvoid drawScene();
GLvoid Reshape(int w, int h);

GLvoid char_key_down(unsigned char key, int x, int y);
GLvoid char_key_up(unsigned char key, int x, int y);

GLvoid Timer(int value);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);

void main(int argc, char** argv)
{
	srand(time(NULL));

	// ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HIEGHT);	// �������� ũ�Ⱑ �ƴ϶� �۾������� ũ����
	GLint wnd_id = glutCreateWindow("To the Light");

	// GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	framework.Initialize();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(nullptr);

	glutTimerFunc(TIMERCLOCK, Timer, 0);
	glutKeyboardFunc(char_key_down);
	glutKeyboardUpFunc(char_key_down);
	glutKeyboardUpFunc(char_key_up);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutMainLoop();

	framework.Release();
}


GLvoid drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	framework.Draw();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	// â ũ�Ⱑ ����� �� �Ҹ�
	//glutReshapeWindow(CLIENT_WIDTH, CLIENT_HIEGHT);
	glViewport(0, 0, w, h);
}

GLvoid char_key_down(unsigned char key, int x, int y)
{

	switch (key) {

	case ' ':
		framework.HandleEvent(Event::SPACE_KEY_DOWN, x, y);
		break;

	case '\r':
	case '\n':
	case '\r\n':
		framework.HandleEvent(Event::RETURN_KEY_DOWN, x, y);
		break;

	case 'W':
	case 'w':
		framework.HandleEvent(Event::W_KEY_DOWN, x, y);
		break;

	case 'A':
	case 'a':
		framework.HandleEvent(Event::A_KEY_DOWN, x, y);
		break;

	case 'S':
	case 's':
		framework.HandleEvent(Event::S_KEY_DOWN, x, y);
		break;

	case 'D':
	case 'd':
		framework.HandleEvent(Event::D_KEY_DOWN, x, y);
		break;

	case 'Q':
	case 'q':
		//glutLeaveMainLoop();
		break;
	}

}

GLvoid char_key_up(unsigned char key, int x, int y)
{
	switch (key) {

	case ' ':
		framework.HandleEvent(Event::SPACE_KEY_UP, x, y);
		break;

	case '\r':
	case '\n':
	case '\r\n':
		framework.HandleEvent(Event::RETURN_KEY_UP, x, y);
		break;

	case 'W':
	case 'w':
		framework.HandleEvent(Event::W_KEY_UP, x, y);
		break;

	case 'A':
	case 'a':
		framework.HandleEvent(Event::A_KEY_UP, x, y);
		break;

	case 'S':
	case 's':
		framework.HandleEvent(Event::S_KEY_UP, x, y);
		break;

	case 'D':
	case 'd':
		framework.HandleEvent(Event::D_KEY_UP, x, y);
		break;

	case 'Q':
	case 'q':
		//glutLeaveMainLoop();
		break;
	}
}


GLvoid special_key_down(unsigned char key, int x, int y)
{
	return GLvoid();
}

GLvoid special_key_up(unsigned char key, int x, int y)
{
	return GLvoid();
}

GLvoid Timer(int value)
{
	framework.Update();
	glutPostRedisplay();
	glutTimerFunc(TIMERCLOCK, Timer, 0);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	// button(��ư�Ķ����) : GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
	// state(�����Ķ����) : GLUT_UP, GLUT_DOWN
	// x, y : �����쿡�����콺����ġ

	switch (button) {
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	}
}

GLvoid Motion(int x, int y)
{
}
