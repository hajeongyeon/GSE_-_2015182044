#pragma once

#include <iostream>

#define MAX_OBJ_COUNT 10

class GameObject
{
private:
	float x, y, size;
	float vx, vy;
	float life, LifeTime;

public:
	float color[4];

	GameObject(float x1, float y1);
	~GameObject() {}

	float getX() { return x; }
	float getY() { return y; }
	float getSize() { return size; }
	void Update(float ElapsedTime);
	float getLife() { return life; }
	float getLifeTime() { return LifeTime; }
};