#pragma once

#include <iostream>
#include "GameObject.h"
#include "Renderer.h"
#include "Sound.h"

class SceneMgr
{
private:
	Renderer* renderer;
	
	GameObject* Bgr;
	GameObject* buildingObj[6];
	GameObject* actorObj[MAX_OBJ_COUNT];
	GameObject* bulletObj[MAX_BL_COUNT];

	GLuint textureBuilding1;
	GLuint textureBuilding2;
	GLuint textureBgr;
	GLuint textureRabbit;
	GLuint textureDog;
	GLuint textureEffect;

	Sound* sound;

	float team1time, team2time, runtime, effecttime, climatetime;
	int rabbitX, DogX, DogY;
	int soundBG;

public:
	SceneMgr();
	~SceneMgr();

	void DrawSolidRect();

	void AddBuildingObj();
	int AddObj(float x, float y, int type, int team);
	void UpdateObj(float elapsedTime);
	void DeleteObj(int idx);

	void Collision();
	bool CollisionRect(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);

	float getTeam2Time() { return team2time; }
};

