#pragma once

#include <iostream>

class GameObject
{
private:
	float x, y, z, size;

public:
	GameObject() {}
	GameObject(float x1, float y1, float z1, float size1) { x = x1; y = y1; z = z1; size = size1; }
	~GameObject() {}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }
	float GetSize() { return size; }
};

class Player : public GameObject
{

};

class Monster : public GameObject
{

};

class Prop : public GameObject
{

};