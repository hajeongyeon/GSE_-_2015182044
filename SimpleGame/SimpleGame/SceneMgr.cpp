#include "stdafx.h"
#include "SceneMgr.h"
#include <time.h>

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
}

int SceneMgr::AddObj(float x, float y)
{
	for (int i = 0; i < MAX_OBJ_COUNT; ++i) {
		if (m_obj[i] == NULL) {
			m_obj[i] = new GameObject(x, y);
			return i;
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

void SceneMgr::UpdateObj(float ElapsedTime)
{
	DoCollision();

	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		if (m_obj[i] != NULL)
		{
			if (m_obj[i]->getLife() < 0.0001f || m_obj[i]->getLifeTime() < 0.0001f)
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
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJ_COUNT; i++)
	{
		collisionCount = 0;
		if (m_obj[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJ_COUNT; j++)
			{
				if (i == j)
					continue;

				if (m_obj[j] != NULL)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					minX = m_obj[i]->getX() - m_obj[i]->getSize() / 2.f;
					minY = m_obj[i]->getY() - m_obj[i]->getSize() / 2.f;
					maxX = m_obj[i]->getX() + m_obj[i]->getSize() / 2.f;
					maxY = m_obj[i]->getY() + m_obj[i]->getSize() / 2.f;
					minX1 = m_obj[j]->getX() - m_obj[j]->getSize() / 2.f;
					minY1 = m_obj[j]->getY() - m_obj[j]->getSize() / 2.f;
					maxX1 = m_obj[j]->getX() + m_obj[j]->getSize() / 2.f;
					maxY1 = m_obj[j]->getY() + m_obj[j]->getSize() / 2.f;
					if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{
						collisionCount++;
					}
				}
			}
			if (collisionCount > 0)
			{
				m_obj[i]->color[0] = 1;
				m_obj[i]->color[1] = 0;
				m_obj[i]->color[2] = 0;
				m_obj[i]->color[3] = 1;
			}
			else
			{
				m_obj[i]->color[0] = 1;
				m_obj[i]->color[1] = 1;
				m_obj[i]->color[2] = 1;
				m_obj[i]->color[3] = 1;
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