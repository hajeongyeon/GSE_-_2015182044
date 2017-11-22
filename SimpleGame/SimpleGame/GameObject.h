#pragma once
#include <cstdlib>

#define MAX_OBJ_COUNT 300
#define MAX_BL_COUNT 100

#define OBJECT_BUILDING 1
#define OBJECT_CHARACTER 2
#define OBJECT_BULLET 3
#define OBJECT_ARROW 4

#define TEAM1 101
#define TEAM2 102

class GameObject
{
private:
	float x, y, size;
	float vx, vy;

	int objType;
	int team;
	float level;

	float life;
	float LifeTime = 100000.f;

	float characterTime;
	float bulletTime;
	float arrowTime;

public:
	float color[4];

	GameObject() {};
	GameObject(float x, float y, int type, int team);
	~GameObject() {};

	void Update(float ElapsedTime);

	float getX() { return x; }
	float getY() { return y; }
	float getSize() { return size; }
	int getType() { return objType; }
	int getTeam() { return team; }
	float getLevel() { return level; }
	float getLife() { return life; }
	float getLifeTime() { return LifeTime; }
	float getBulletTime() { return bulletTime; }
	float getArrowTime() { return arrowTime; }
	float getCharacterTime() { return characterTime; }

	void SetLife(float currentlife) { life = currentlife; }
	void SetArrowTime(float time) { arrowTime = time; }
	void SetBulletTime(float time) { bulletTime = time; }
	void SetCharacterTime(float time) { characterTime = time; }
	void SetDamage(float damage) { life -= damage; }
};

