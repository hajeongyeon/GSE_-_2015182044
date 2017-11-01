#include "stdafx.h"
#include "SceneMgr.h"
#include <time.h>
#include <Windows.h>

SceneMgr::SceneMgr(int width, int height)
{
	renderer = new Renderer(width, height);

	if(renderer->IsInitialized())
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";

	WindowWidth = width;
	WindowHeight = height;

	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
		m_obj[i] = NULL;
}

void SceneMgr::DrawObj()
{
	renderer->DrawSolidRect(0, 0, 0, WindowWidth, 0, 0, 0, 0.4);

	renderer->DrawSolidRect(buildingObj->getX(), buildingObj->getY(), 0, 30, 1, 1, 0, 0);

	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		if (m_obj[i] != NULL)
		{
			// Renderer Test
			renderer->DrawSolidRect(
				m_obj[i]->getX(),
				m_obj[i]->getY(),
				0,
				m_obj[i]->getSize(),
				m_obj[i]->color[0],
				m_obj[i]->color[1],
				m_obj[i]->color[2],
				m_obj[i]->color[3]
			);
		}
	}

	for (int i = 0; i < MAX_OBJ_COUNT; ++i) {
		if (bulletObj[i] != NULL) {
			renderer->DrawSolidRect(bulletObj[i]->getX(), bulletObj[i]->getY(), 0, 5, 0, 1, 0, 0);
		}
	}
}

int SceneMgr::AddObj(float x, float y, int obj)
{
	if (obj == OBJECT_CHARACTER) {
		for (int i = 0; i < MAX_OBJ_COUNT; ++i) {
			if (m_obj[i] == NULL) {
				m_obj[i] = new GameObject(x, y);
				m_obj[i]->SetLife(100.f);
				return i;
			}
		}
	}
	else if (obj == OBJECT_BUILDING) {
		buildingObj = new GameObject(x, y);
		buildingObj->SetLife(100.f);
		return 0;
	}
	else if (obj == OBJECT_BULLET) {
		for (int i = 0; i < MAX_OBJ_COUNT; ++i) {
			if (bulletObj[i] == NULL) {
				bulletObj[i] = new GameObject(x, y);
				bulletObj[i]->SetLife(20.f);
				return i;
			}
		}
	}

	std::cout << "slots are full \n";
	return -1;
}

void SceneMgr::DeleteObj(int idx)
{
	if (m_obj[idx] != NULL)
	{
		delete m_obj[idx];
		m_obj[idx] = NULL;
	}
}

void SceneMgr::DeleteBLObj(int idx)
{
	if (bulletObj[idx] != NULL)
	{
		delete bulletObj[idx];
		bulletObj[idx] = NULL;
	}
}

void SceneMgr::UpdateObj(float ElapsedTime)
{
	DoCollision();

	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		if (m_obj[i] != NULL)
		{
			if (m_obj[i]->life < 0.0001f || m_obj[i]->getLifeTime() < 0.0001f)
			{
				//kill object
				delete m_obj[i];
				m_obj[i] = NULL;
			}
			else
			{
				m_obj[i]->Update(ElapsedTime);
			}
		}
		if (bulletObj[i] != NULL)
		{
			bulletObj[i]->Update(ElapsedTime);
		}
	}
}

void SceneMgr::DoCollision()
{
	int collisionBDCount = 0;		// ºôµù°ú Ãæµ¹
	int collisionBLCount = 0;		// ÃÑ¾Ë°ú Ãæµ¹

	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		collisionBDCount = 0;

		if (m_obj[i] != NULL)
		{
			float minX, minY;
			float maxX, maxY;

			float minX1, minY1;
			float maxX1, maxY1;

			float minX2, minY2;
			float maxX2, maxY2;

			minX = m_obj[i]->getX() - m_obj[i]->getSize() / 2.f;
			minY = m_obj[i]->getY() - m_obj[i]->getSize() / 2.f;
			maxX = m_obj[i]->getX() + m_obj[i]->getSize() / 2.f;
			maxY = m_obj[i]->getY() + m_obj[i]->getSize() / 2.f;
			minX1 = buildingObj->getX() - 10;
			minY1 = buildingObj->getY() - 10;
			maxX1 = buildingObj->getX() + 10;
			maxY1 = buildingObj->getY() + 10;
			minX2 = bulletObj[i]->getX() - 2.5f;
			minY2 = bulletObj[i]->getY() - 2.5f;
			maxX2 = bulletObj[i]->getX() + 2.5f;
			maxY2 = bulletObj[i]->getY() + 2.5f;
			if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
			{
				collisionBDCount++;
			}
			if (CollisionRect(minX, minY, maxX, maxY, minX2, minY2, maxX2, maxY2))
			{
				collisionBLCount++;
			}

			if (collisionBDCount > 0)
			{
				DeleteObj(i);

				buildingObj->life -= 10.f;

				if (buildingObj->life < 0.f)
					delete buildingObj;
			}
			if (collisionBLCount > 0) {
				// DeleteBLObj(i);

				m_obj[i]->life -= bulletObj[i]->life;

				if (m_obj[i]->life < 0.f)
					DeleteObj(i);
			}
		}
	}
}

bool SceneMgr::CollisionRect(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}