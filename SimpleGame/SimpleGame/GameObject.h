#pragma once
#include <cstdlib>

#define MAX_OBJ_COUNT 300
#define MAX_BL_COUNT 100

#define OBJECT_BUILDING 1
#define OBJECT_CHARACTER 2
#define OBJECT_BULLET 3
#define OBJECT_ARROW 4

class GameObject
{
private:
	float x, y, size;
	float vx, vy;
	int objType;
	float life;
	float LifeTime = 100000.f;
	float bulletTime;
	float arrowTime;

public:
	float color[4];

	GameObject() {};
	GameObject(float x, float y, int type);
	~GameObject() {};

	void Update(float ElapsedTime);

	float getX() { return x; }
	float getY() { return y; }
	float getSize() { return size; }
	float getType() { return objType; }
	float getLife() { return life; }
	float getBulletTime() { return bulletTime; }
	float getArrowTime() { return arrowTime; }
	float getLifeTime() { return LifeTime; }

	void SetLife(float currentlife) { life = currentlife; }
	void SetArrowTime(float time) { arrowTime = time; }
	void SetBulletTime(float time) { bulletTime = time; }
	void SetDamage(float damage) { life -= damage; }
};

