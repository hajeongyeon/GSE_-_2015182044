#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	renderer = new Renderer(500, 500);

	if (!renderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";

	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
		actorObj[i] = NULL;

	for (int i = 0; i < MAX_BL_COUNT; ++i)
		bulletObj[i] = NULL;

	textureBuilding = renderer->CreatePngTexture("./Resource/building.png");
}

SceneMgr::~SceneMgr()
{
	if (buildingObj != NULL)
		delete buildingObj;

	for (int i = 0; i < MAX_BL_COUNT; ++i)
		if (bulletObj[i] != NULL)
			delete bulletObj[i];

	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
		if (actorObj[i] != NULL)
			delete actorObj[i];

	delete renderer;
	delete[] bulletObj;
	delete[] actorObj;
}

void SceneMgr::DrawSolidRect()
{
	if (buildingObj != NULL)
		renderer->DrawTexturedRect(buildingObj->getX(), buildingObj->getY(), 0,
			buildingObj->getSize(), buildingObj->color[0], buildingObj->color[1], buildingObj->color[2], buildingObj->color[3], textureBuilding);

	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
		if (actorObj[i] != NULL)
			renderer->DrawSolidRect(actorObj[i]->getX(), actorObj[i]->getY(), 0,
				actorObj[i]->getSize(), actorObj[i]->color[0], actorObj[i]->color[1], actorObj[i]->color[2], actorObj[i]->color[3]);

	for(int i =0; i< MAX_BL_COUNT; ++i)
		if (bulletObj[i] != NULL)
			renderer->DrawSolidRect(bulletObj[i]->getX(), bulletObj[i]->getY(), 0,
				bulletObj[i]->getSize(), bulletObj[i]->color[0], bulletObj[i]->color[1], bulletObj[i]->color[2], bulletObj[i]->color[3]);
}


int SceneMgr::AddObj(float x, float y, int type)
{
	if (type == OBJECT_BUILDING) {
		buildingObj = new GameObject(x, y, type);
	}
	else if (type == OBJECT_BULLET) {
		for (int i = 0; i < MAX_BL_COUNT; i++) {
			if (bulletObj[i] == NULL) {
				bulletObj[i] = new GameObject(x, y, type);
				return i;
			}
		}
	}
	else {
		for (int i = 0; i < MAX_OBJ_COUNT; i++) {
			if (actorObj[i] == NULL) {
				actorObj[i] = new GameObject(x, y, type);
				return i;
			}
		}
	}
}

void SceneMgr::UpdateObj(float elapsedTime)
{
	Collision();

	if (buildingObj != NULL) {
		if (buildingObj->getLife() < 0.0001f) {
			delete buildingObj;
			buildingObj = NULL;
		}
		else {
			buildingObj->Update(elapsedTime);

			if (buildingObj->getBulletTime() > 0.5f) {
				AddObj(buildingObj->getX(), buildingObj->getY(), OBJECT_BULLET);
				buildingObj->SetBulletTime(0.f);
			}
		}
	}

	for (int i = 0; i < MAX_BL_COUNT; ++i) {
		if (bulletObj[i] != NULL) {
			if (bulletObj[i]->getLife() < 0.0001f) {
				delete bulletObj[i];
				bulletObj[i] = NULL;
			}
			else
				bulletObj[i]->Update(elapsedTime);
		}
	}

	for (int i = 0; i < MAX_OBJ_COUNT; i++) {
		if (actorObj[i] != NULL) {
			if (actorObj[i]->getLife() <= 0.f) {
				DeleteObj(i);
			}
			else {
				actorObj[i]->Update(elapsedTime);

				if (actorObj[i]->getType() == OBJECT_CHARACTER) {
					if (actorObj[i]->getArrowTime() > 0.5f) {
						AddObj(actorObj[i]->getX(), actorObj[i]->getY(), OBJECT_ARROW);
						actorObj[i]->SetArrowTime(0.f);
					}
				}
			}
		}
	}
}

void SceneMgr::DeleteObj(int index)
{
	if (actorObj[index] != NULL)
	{
		delete actorObj[index];
		actorObj[index] = NULL;
	}
}

void SceneMgr::Collision()
{
	// building and (character, arrow) collision
	if (buildingObj != NULL) {
		for (int i = 0; i < MAX_OBJ_COUNT; i++) {
			if (actorObj[i] != NULL) {
				float minX, minY;
				float maxX, maxY;
				float minX1, minY1;
				float maxX1, maxY1;

				minX = actorObj[i]->getX() - actorObj[i]->getSize() / 2.f;
				minY = actorObj[i]->getY() - actorObj[i]->getSize() / 2.f;
				maxX = actorObj[i]->getX() + actorObj[i]->getSize() / 2.f;
				maxY = actorObj[i]->getY() + actorObj[i]->getSize() / 2.f;
				minX1 = buildingObj->getX() - buildingObj->getSize() / 2.f;
				minY1 = buildingObj->getY() - buildingObj->getSize() / 2.f;
				maxX1 = buildingObj->getX() + buildingObj->getSize() / 2.f;
				maxY1 = buildingObj->getY() + buildingObj->getSize() / 2.f;

				if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1)) {
					buildingObj->SetDamage(actorObj[i]->getLife());
					actorObj[i]->SetLife(0.f);
				}
			}
		}
	}

	// character and bullet
	for (int i = 0; i < MAX_OBJ_COUNT; i++) {
		if (actorObj[i] != NULL) {
			for (int j = 0; j < MAX_BL_COUNT; j++) {
				if (bulletObj[j] != NULL) {
					float minX, minY;
					float maxX, maxY;
					float minX1, minY1;
					float maxX1, maxY1;

					minX = actorObj[i]->getX() - actorObj[i]->getSize() / 2.f;
					minY = actorObj[i]->getY() - actorObj[i]->getSize() / 2.f;
					maxX = actorObj[i]->getX() + actorObj[i]->getSize() / 2.f;
					maxY = actorObj[i]->getY() + actorObj[i]->getSize() / 2.f;
					minX1 = bulletObj[j]->getX() - bulletObj[j]->getSize() / 2.f;
					minY1 = bulletObj[j]->getY() - bulletObj[j]->getSize() / 2.f;
					maxX1 = bulletObj[j]->getX() + bulletObj[j]->getSize() / 2.f;
					maxY1 = bulletObj[j]->getY() + bulletObj[j]->getSize() / 2.f;

					if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1)) {
						if (actorObj[i]->getType() == OBJECT_CHARACTER) {
							bulletObj[j]->SetDamage(actorObj[i]->getLife());
							actorObj[i]->SetDamage(bulletObj[j]->getLife());
							bulletObj[j]->SetLife(0.f);
							actorObj[i]->SetLife(0.f);
						}
					}
				}
			}
		}
	}

	// character and arrow
	for (int i = 0; i < MAX_OBJ_COUNT; i++) {
		if (actorObj[i] != NULL) {
			for (int j = i + 1; j < MAX_OBJ_COUNT; j++) {
				if (actorObj[j] != NULL && actorObj[i] != NULL) {
					float minX, minY;
					float maxX, maxY;
					float minX1, minY1;
					float maxX1, maxY1;

					minX = actorObj[i]->getX() - actorObj[i]->getSize() / 2.f;
					minY = actorObj[i]->getY() - actorObj[i]->getSize() / 2.f;
					maxX = actorObj[i]->getX() + actorObj[i]->getSize() / 2.f;
					maxY = actorObj[i]->getY() + actorObj[i]->getSize() / 2.f;
					minX1 = actorObj[j]->getX() - actorObj[j]->getSize() / 2.f;
					minY1 = actorObj[j]->getY() - actorObj[j]->getSize() / 2.f;
					maxX1 = actorObj[j]->getX() + actorObj[j]->getSize() / 2.f;
					maxY1 = actorObj[j]->getY() + actorObj[j]->getSize() / 2.f;

					if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1)) {
						if ((actorObj[i]->getType() == OBJECT_CHARACTER) && (actorObj[j]->getType() == OBJECT_ARROW)) {
							actorObj[i]->SetDamage(actorObj[j]->getLife());
						}
					}
				}
			}
		}
	}
}

bool SceneMgr::CollisionRect(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}