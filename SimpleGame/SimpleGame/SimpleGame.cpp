/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "GameObject.h"
#include "SceneMgr.h"

SceneMgr *g_SceneMgr = NULL;

DWORD g_prevTime = 0; 

bool g_LButtonDown = false;

void RenderScene(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currentTime = timeGetTime();
	DWORD elapsedTime = currentTime - g_prevTime;
	g_prevTime = currentTime;

	g_SceneMgr->UpdateObj((float)elapsedTime);
	g_SceneMgr->DrawObj();

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
			//clicked
			// for (int i = 0; i < 100; i++)
				g_SceneMgr->AddObj(x - 250, -y + 250, OBJECT_CHARACTER);
		}
		g_LButtonDown = false;
	}

	RenderScene();
}

void MotionInput(int x, int y)
{
	if (g_LButtonDown)
	{
		//clicked
		for (int i = 0; i < 100; i++)
		{
			//g_SceneMgr->AddObj(x - 250, -y + 250);
		}
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
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_SceneMgr = new SceneMgr(500, 500);

	g_SceneMgr->AddObj(0, 0, OBJECT_BUILDING);

	for (int i = 0; i < 200; i++)
	{
		float x = 250.f * 2.f * ((float)std::rand() / (float)RAND_MAX - 0.5f);
		float y = 250.f * 2.f * ((float)std::rand() / (float)RAND_MAX - 0.5f);

		g_SceneMgr->AddObj(x, y, OBJECT_CHARACTER);
	}

	for (int i = 0; i < 100; ++i) {
		g_SceneMgr->AddObj(0, 0, OBJECT_BULLET);
	}

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete g_SceneMgr;

    return 0;
}

