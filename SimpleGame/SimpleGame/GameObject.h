#pragma once

#include <iostream>

#define MAX_OBJ_COUNT 50

class GameObject
{
private:
	float x, y, size;
	float vx = 1, vy = 0;

public:
	GameObject() {}
	GameObject(float x1, float y1, float size1) { x = x1; y = y1; size = size1; }
	~GameObject() {}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetSize() { return size; }

	void Update();
};