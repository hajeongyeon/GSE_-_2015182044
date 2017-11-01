#pragma once

#include <iostream>

#define MAX_OBJ_COUNT 100

class GameObject
{
private:
	float x, y, size;
	float vx, vy;
	float LifeTime;

public:
	float color[4];
	float life;

	GameObject(float x1, float y1);
	~GameObject() {}

	float getX() { return x; }
	float getY() { return y; }
	float getSize() { return size; }
	void Update(float ElapsedTime);
	void SetLife(float slife) { life = slife; }
	float getLifeTime() { return LifeTime; }
};