#pragma once

#include <iostream>
#include "GameObject.h"
#include "Renderer.h"

class SceneMgr
{
private:
	Renderer* renderer;

	GameObject* buildingObj;
	GameObject* actorObj[MAX_OBJ_COUNT];
	GameObject* bulletObj[MAX_BL_COUNT];

	GLuint textureBuilding;

public:
	SceneMgr();
	~SceneMgr();

	void DrawSolidRect();

	int AddObj(float x, float y, int type);
	void UpdateObj(float elapsedTime);
	void DeleteObj(int idx);

	void Collision();
	bool CollisionRect(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
};

