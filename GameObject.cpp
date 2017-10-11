#include "stdafx.h"
#include "GameObject.h"
#include <math.h>

void GameObject::Update()
{
	vx = speed * cos(30);
	vy = speed * sin(30);

	float xtime = 1.5;
	x = x + vx * xtime;
	y = y + vy * xtime;

	if (x > 250 || x < -250)
		x = -x;
	if (y > 250 || y < -250)
		y = -y;
}