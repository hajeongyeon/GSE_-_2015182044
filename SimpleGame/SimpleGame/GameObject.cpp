#include "stdafx.h"
#include "GameObject.h"
#include <math.h>

void GameObject::Update()
{
	float xtime = 1.5;
	x = x + vx * xtime;
	y = y + vy * xtime;

	if (x > 250 || x < -250)
		x = -x;
}