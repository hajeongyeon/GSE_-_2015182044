#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(float x, float y, int type) :x(x), y(y), size(size), objType(type)
{
	bulletTime = 0.f;
	arrowTime = 0.f;

	if (type == OBJECT_CHARACTER)
	{
		for (int i = 0; i < 4; ++i)
			color[i] = 1;

		vx = 300.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vy = 300.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

		size = 10;
		life = 10;
	}
	else if (type == OBJECT_BUILDING)
	{
		color[0] = 1;
		color[1] = 0;
		color[2] = 1;
		color[3] = 1;

		vx = 0;
		vy = 0;

		size = 30;
		life = 500;
	}
	else if (type == OBJECT_BULLET)
	{
		color[0] = 1;
		color[1] = 0;
		color[2] = 0;
		color[3] = 1;

		vx = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vy = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

		size = 2;
		life = 20;
	}
	else if (type == OBJECT_ARROW)
	{
		color[0] = 0;
		color[1] = 1;
		color[2] = 0;
		color[3] = 1;

		vx = 100.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vy = 100.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

		size = 2;
		life = 10;
	}
}

void GameObject::Update(float elapsedTime)
{
	float ElapsedTimeInSecond = elapsedTime / 1000;

	bulletTime += ElapsedTimeInSecond;
	arrowTime += ElapsedTimeInSecond;

	x = x + vx * ElapsedTimeInSecond;
	y = y + vy * ElapsedTimeInSecond;

	if (x > 250 || x < -250) {
		if (objType == OBJECT_BULLET || objType == OBJECT_ARROW)
			life = 0.f;
		vx = -vx;
	}
	if (y > 250 || y < -250) {
		if (objType == OBJECT_BULLET || objType == OBJECT_ARROW)
			life = 0.f;
		vy = -vy;
	}

	//if (life > 0.f)
	//	life -= 0.5f;
	//if (LifeTime > 0.f)
	//	LifeTime -= ElapsedTimeInSecond;
}