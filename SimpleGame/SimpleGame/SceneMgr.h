#pragma once

#include "GameObject.h"

class SceneMgr
{
public:
	GameObject* m_obj[MAX_OBJ_COUNT];
	
	void AddObj();
};