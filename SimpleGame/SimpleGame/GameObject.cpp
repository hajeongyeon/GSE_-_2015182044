#include "stdafx.h"
#include "GameObject.h"
#include <math.h>

GameObject::GameObject(float x1, float y1)
{
	x = x1;
	y = y1;
	vx = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	vy = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

	size = 10;

	for (int i = 0; i < 4; ++i)
		color[i] = 1;

	LifeTime = 100000.f;
}

void GameObject::Update(float ElapsedTime)
{
	float ElapsedTimeInSecond = ElapsedTime / 1000.f;

	x = x + vx * ElapsedTimeInSecond;
	y = y + vy * ElapsedTimeInSecond;

	if (x > 250 || x < -250)
		vx = -vx;
	if (y > 250 || y < -250)
		vy = -vy;

	//if (life > 0.f)
	//	life -= 0.5f;
	//if (LifeTime > 0.f)
	//	LifeTime -= ElapsedTimeInSecond;
}