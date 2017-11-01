#pragma once

#include "GameObject.h"
#include "Renderer.h"

#define OBJECT_BUILDING 1
#define OBJECT_CHARACTER 2
#define OBJECT_BULLET 3
#define OBJECT_ARROW 4

class SceneMgr
{
public:
	int WindowWidth;
	int WindowHeight;

	GameObject* m_obj[MAX_OBJ_COUNT];
	GameObject* bulletObj[MAX_OBJ_COUNT];
	GameObject* buildingObj;
	Renderer* renderer;

public:
	SceneMgr(int width, int height);
	~SceneMgr() {}

	void DrawObj();
	int AddObj(float x, float y, int obj);
	void DeleteObj(int idx);
	GameObject* GetObj(int n) const { return m_obj[n]; }
	void UpdateObj(float ElapsedTime);

	void DoCollision();
	bool CollisionRect(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
};