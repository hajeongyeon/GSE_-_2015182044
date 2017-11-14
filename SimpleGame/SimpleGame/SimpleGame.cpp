#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include "SceneMgr.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

SceneMgr *mgr = NULL;

DWORD g_startTime = NULL;

bool g_LButtonDown = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_startTime;
	g_startTime = currTime;
	
	mgr->UpdateObj((float)elapsedTime);
	mgr->DrawSolidRect();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_LButtonDown = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (g_LButtonDown)
		{
			for (int i = 0; i < 1; i++)
				mgr->AddObj(x - 250, -y + 250, OBJECT_CHARACTER);
		}
		g_LButtonDown = false;
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
		std::cout << " GLEW Version is 3.0\n ";
	else
		std::cout << "GLEW 3.0 not supported\n ";

	mgr = new SceneMgr();
	mgr->AddObj(0, 0, OBJECT_BUILDING);
	g_startTime = timeGetTime();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete mgr;

	return 0;
}

