#include "stdafx.h"
#include "SceneMgr.h"
#include <time.h>

SceneMgr::SceneMgr()
{
	renderer = new Renderer(500, 700);

	if (!renderer->IsInitialized())
		std::cout << "Renderer could not be initialized.. \n";

	for (int i = 0; i < 6; ++i)
		buildingObj[i] = NULL;

	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
		actorObj[i] = NULL;

	for (int i = 0; i < MAX_BL_COUNT; ++i)
		bulletObj[i] = NULL;

	textureBuilding1 = renderer->CreatePngTexture("./Resource/team1building.png");
	textureBuilding2 = renderer->CreatePngTexture("./Resource/team2building.png");
	textureBgr = renderer->CreatePngTexture("./Resource/background.png");
	textureRabbit = renderer->CreatePngTexture("./Resource/rabbit.png");
	textureDog = renderer->CreatePngTexture("./Resource/dog2.png");
	textureEffect = renderer->CreatePngTexture("./Resource/effect.png");

	team1time = 0.f;
	team2time = 7.f;
	effecttime = 0.f;

	rabbitX = 0;
	DogX = 0;
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < 6; ++i)
		if (buildingObj[i] != NULL)
			buildingObj[i] = NULL;

	for (int i = 0; i < MAX_BL_COUNT; ++i)
		if (bulletObj[i] != NULL)
			delete bulletObj[i];

	for (int i = 0; i < MAX_OBJ_COUNT; ++i)
		if (actorObj[i] != NULL)
			delete actorObj[i];

	delete renderer;
	delete[] buildingObj;
	delete[] bulletObj;
	delete[] actorObj;
}

void SceneMgr::DrawSolidRect()
{
	renderer->DrawTexturedRect(0, 0, 0, 700, 1, 1, 1, 1, textureBgr, 0.5);

	for (int i = 0; i < 3; ++i) {
		if (buildingObj[i] != NULL) {
			renderer->DrawTexturedRect(buildingObj[i]->getX(), buildingObj[i]->getY(), 0, buildingObj[i]->getSize(),
				buildingObj[i]->color[0], buildingObj[i]->color[1], buildingObj[i]->color[2], buildingObj[i]->color[3],
				textureBuilding1, buildingObj[i]->getLevel());
			renderer->DrawSolidRectGauge(buildingObj[i]->getX(), buildingObj[i]->getY() + 60, 0,
				100, 5, 1, 0, 0, 1, buildingObj[i]->getLife() / 500, buildingObj[i]->getLevel());
		}
	}

	for (int i = 3; i < 6; ++i) {
		if (buildingObj[i] != NULL) {
			renderer->DrawTexturedRect(buildingObj[i]->getX(), buildingObj[i]->getY(), 0, buildingObj[i]->getSize(),
				buildingObj[i]->color[0], buildingObj[i]->color[1], buildingObj[i]->color[2], buildingObj[i]->color[3],
				textureBuilding2, buildingObj[i]->getLevel());
			renderer->DrawSolidRectGauge(buildingObj[i]->getX(), buildingObj[i]->getY() + 60, 0,
				100, 5, 0, 0, 1, 1, buildingObj[i]->getLife() / 500, buildingObj[i]->getLevel());
		}
	}

	for (int i = 0; i < MAX_OBJ_COUNT; ++i) {
		if (actorObj[i] != NULL) {
			if (actorObj[i]->getType() == OBJECT_CHARACTER) {
				if (actorObj[i]->getTeam() == TEAM1) {
					renderer->DrawTexturedRectSeq(actorObj[i]->getX(), actorObj[i]->getY(), 0, actorObj[i]->getSize(),
						actorObj[i]->color[0], actorObj[i]->color[1], actorObj[i]->color[2], actorObj[i]->color[3], textureRabbit,
						rabbitX, 0, 8, 1, actorObj[i]->getLevel());
					renderer->DrawSolidRectGauge(actorObj[i]->getX(), actorObj[i]->getY() + 20, 0,
						40, 5, 1, 0, 0, 1, actorObj[i]->getLife() / 100, actorObj[i]->getLevel());
				}
				else {
					renderer->DrawTexturedRectSeq(actorObj[i]->getX(), actorObj[i]->getY(), 0, actorObj[i]->getSize(),
						actorObj[i]->color[0], actorObj[i]->color[1], actorObj[i]->color[2], actorObj[i]->color[3], textureDog,
						DogX, 0, 9, 1, actorObj[i]->getLevel());
					renderer->DrawSolidRectGauge(actorObj[i]->getX(), actorObj[i]->getY() + 20, 0,
						40, 5, 0, 0, 1, 1, actorObj[i]->getLife() / 100, actorObj[i]->getLevel());
				}
			}
			else {
				renderer->DrawSolidRect(actorObj[i]->getX(), actorObj[i]->getY(), 0, actorObj[i]->getSize(),
					actorObj[i]->color[0], actorObj[i]->color[1], actorObj[i]->color[2], actorObj[i]->color[3], actorObj[i]->getLevel());
			}
		}
	}

	for (int i = 0; i < MAX_BL_COUNT; ++i) {
		if (bulletObj[i] != NULL) {
			if (bulletObj[i]->getVY() < 0)
				renderer->DrawParticle(bulletObj[i]->getX(), bulletObj[i]->getY(), 0, bulletObj[i]->getSize(),
					bulletObj[i]->color[0], bulletObj[i]->color[1], bulletObj[i]->color[2], bulletObj[i]->color[3],
					0, 1, textureEffect, effecttime);
			else if (bulletObj[i]->getVY() > 0)
				renderer->DrawParticle(bulletObj[i]->getX(), bulletObj[i]->getY(), 0, bulletObj[i]->getSize(),
					bulletObj[i]->color[0], bulletObj[i]->color[1], bulletObj[i]->color[2], bulletObj[i]->color[3],
					0, -1, textureEffect, effecttime);
			else 
				renderer->DrawParticle(bulletObj[i]->getX(), bulletObj[i]->getY(), 0, bulletObj[i]->getSize(),
					bulletObj[i]->color[0], bulletObj[i]->color[1], bulletObj[i]->color[2], bulletObj[i]->color[3],
					0, 0, textureEffect, effecttime);
		}
	}
}

void SceneMgr::AddBuildingObj()
{
	Bgr = new GameObject(0, 0, 0, 0);

	buildingObj[0] = new GameObject(-150, 250, OBJECT_BUILDING, TEAM1);
	buildingObj[1] = new GameObject(0, 250, OBJECT_BUILDING, TEAM1);
	buildingObj[2] = new GameObject(150, 250, OBJECT_BUILDING, TEAM1);
	buildingObj[3] = new GameObject(-150, -250, OBJECT_BUILDING, TEAM2);
	buildingObj[4] = new GameObject(0, -250, OBJECT_BUILDING, TEAM2);
	buildingObj[5] = new GameObject(150, -250, OBJECT_BUILDING, TEAM2);
}

int SceneMgr::AddObj(float x, float y, int type, int team)
{
	if (type == OBJECT_BULLET) {
		for (int i = 0; i < MAX_BL_COUNT; i++) {
			if (bulletObj[i] == NULL) {
				bulletObj[i] = new GameObject(x, y, type, team);
				return i;
			}
		}
	}
	else {
		for (int i = 0; i < MAX_OBJ_COUNT; i++) {
			if (actorObj[i] == NULL) {
				actorObj[i] = new GameObject(x, y, type, team);

				if (type == OBJECT_CHARACTER && team == TEAM2)
					team2time = 0;

				return i;
			}
		}
	}
}

void SceneMgr::UpdateObj(float elapsedTime)
{
	team1time += elapsedTime / 1000;
	team2time += elapsedTime / 1000;
	runtime += elapsedTime / 1000;
	effecttime += elapsedTime / 1000;

	if (runtime >= 0.1f) {
		rabbitX += 1;
		if (rabbitX >= 8)
			rabbitX = 0;

		DogX += 1;
		if (DogX >= 9)
			DogX = 0;

		runtime = 0.f;
	}

	srand((unsigned int)time(NULL));

	Collision();

	// building life 贸府, 诀单捞飘 棺 bullet 积己
	for (int i = 0; i < 6; ++i) {
		if (buildingObj[i] != NULL) {
			if (buildingObj[i]->getLife() < 0.0001f) {
				delete buildingObj[i];
				buildingObj[i] = NULL;
			}
			else {
				buildingObj[i]->Update(elapsedTime);

				if (buildingObj[i]->getTeam() == TEAM1) {
					if (buildingObj[i]->getBulletTime() > 5.f) {
						AddObj(buildingObj[i]->getX(), buildingObj[i]->getY(), OBJECT_BULLET, TEAM1);
						buildingObj[i]->SetBulletTime(0.f);
					}
				}
				else {
					if (buildingObj[i]->getBulletTime() > 5.f) {
						AddObj(buildingObj[i]->getX(), buildingObj[i]->getY(), OBJECT_BULLET, TEAM2);
						buildingObj[i]->SetBulletTime(0.f);
					}
				}
			}
		}
	}

	// team1 character 积己
	if (team1time >= 5.f) {
		AddObj(rand() % 500 - 249, rand() % 350, OBJECT_CHARACTER, TEAM1);
		team1time = 0.f;
	}

	// bullet life 贸府 棺 诀单捞飘
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

	// character, arrow life 贸府, 诀单捞飘 棺 arrow 积己
	for (int i = 0; i < MAX_OBJ_COUNT; i++) {
		if (actorObj[i] != NULL) {
			if (actorObj[i]->getLife() <= 0.f) {
				DeleteObj(i);
			}
			else {
				actorObj[i]->Update(elapsedTime);

				if (actorObj[i]->getTeam() == TEAM1) {
					if (actorObj[i]->getType() == OBJECT_CHARACTER) {
						if (actorObj[i]->getArrowTime() > 3.f) {
							AddObj(actorObj[i]->getX(), actorObj[i]->getY(), OBJECT_ARROW, TEAM1);
							actorObj[i]->SetArrowTime(0.f);
						}
					}
				}
				else {
					if (actorObj[i]->getType() == OBJECT_CHARACTER) {
						if (actorObj[i]->getArrowTime() > 3.f) {
							AddObj(actorObj[i]->getX(), actorObj[i]->getY(), OBJECT_ARROW, TEAM2);
							actorObj[i]->SetArrowTime(0.f);
						}
					}
				}
			}
		}
	}
}

void SceneMgr::DeleteObj(int index)
{
	if (actorObj[index] != NULL) {
		delete actorObj[index];
		actorObj[index] = NULL;
	}
}

void SceneMgr::Collision()
{
	// team1 building and team2 (character, arrow) collision
	for (int j = 0; j < 3; j++) {
		if (buildingObj[j] != NULL) {
			for (int i = 0; i < MAX_OBJ_COUNT; i++) {
				if (actorObj[i] != NULL) {
					if (actorObj[i]->getTeam() == TEAM2) {
						float minX, minY;
						float maxX, maxY;
						float minX1, minY1;
						float maxX1, maxY1;

						minX = actorObj[i]->getX() - actorObj[i]->getSize() / 2.f;
						minY = actorObj[i]->getY() - actorObj[i]->getSize() / 2.f;
						maxX = actorObj[i]->getX() + actorObj[i]->getSize() / 2.f;
						maxY = actorObj[i]->getY() + actorObj[i]->getSize() / 2.f;
						minX1 = buildingObj[j]->getX() - buildingObj[j]->getSize() / 2.f;
						minY1 = buildingObj[j]->getY() - buildingObj[j]->getSize() / 2.f;
						maxX1 = buildingObj[j]->getX() + buildingObj[j]->getSize() / 2.f;
						maxY1 = buildingObj[j]->getY() + buildingObj[j]->getSize() / 2.f;

						if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1)) {
							buildingObj[j]->SetDamage(actorObj[i]->getLife());
							actorObj[i]->SetLife(0.f);
						}
					}
				}
			}
		}
	}

	// team2 building and team1 (character, arrow) collision
	for (int j = 3; j < 6; j++) {
		if (buildingObj[j] != NULL) {
			for (int i = 0; i < MAX_OBJ_COUNT; i++) {
				if (actorObj[i] != NULL) {
					if (actorObj[i]->getTeam() == TEAM1) {
						float minX, minY;
						float maxX, maxY;
						float minX1, minY1;
						float maxX1, maxY1;

						minX = actorObj[i]->getX() - actorObj[i]->getSize() / 2.f;
						minY = actorObj[i]->getY() - actorObj[i]->getSize() / 2.f;
						maxX = actorObj[i]->getX() + actorObj[i]->getSize() / 2.f;
						maxY = actorObj[i]->getY() + actorObj[i]->getSize() / 2.f;
						minX1 = buildingObj[j]->getX() - buildingObj[j]->getSize() / 2.f;
						minY1 = buildingObj[j]->getY() - buildingObj[j]->getSize() / 2.f;
						maxX1 = buildingObj[j]->getX() + buildingObj[j]->getSize() / 2.f;
						maxY1 = buildingObj[j]->getY() + buildingObj[j]->getSize() / 2.f;

						if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1)) {
							buildingObj[j]->SetDamage(actorObj[i]->getLife());
							actorObj[i]->SetLife(0.f);
						}
					}
				}
			}
		}
	}

	// character and bullet
	for (int i = 0; i < MAX_OBJ_COUNT; i++) {
		if (actorObj[i] != NULL) {
			for (int j = 0; j < MAX_BL_COUNT; j++) {
				if (bulletObj[j] != NULL) {
					if ((actorObj[i]->getTeam() == TEAM1 && bulletObj[j]->getTeam() == TEAM2) || (actorObj[i]->getTeam() == TEAM2 && bulletObj[j]->getTeam() == TEAM1)) {
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
								actorObj[i]->SetDamage(bulletObj[j]->getLife());
								bulletObj[j]->SetDamage(actorObj[i]->getLife());
							}
						}
					}
				}
			}
		}
	}

	// building and bullet
	for (int i = 0; i < 6; i++) {
		if (buildingObj[i] != NULL) {
			for (int j = 0; j < MAX_BL_COUNT; j++) {
				if (bulletObj[j] != NULL) {
					if ((buildingObj[i]->getTeam() == TEAM1 && bulletObj[j]->getTeam() == TEAM2) || (buildingObj[i]->getTeam() == TEAM2 && bulletObj[j]->getTeam() == TEAM1)) {
						float minX, minY;
						float maxX, maxY;
						float minX1, minY1;
						float maxX1, maxY1;

						minX = buildingObj[i]->getX() - buildingObj[i]->getSize() / 2.f;
						minY = buildingObj[i]->getY() - buildingObj[i]->getSize() / 2.f;
						maxX = buildingObj[i]->getX() + buildingObj[i]->getSize() / 2.f;
						maxY = buildingObj[i]->getY() + buildingObj[i]->getSize() / 2.f;
						minX1 = bulletObj[j]->getX() - bulletObj[j]->getSize() / 2.f;
						minY1 = bulletObj[j]->getY() - bulletObj[j]->getSize() / 2.f;
						maxX1 = bulletObj[j]->getX() + bulletObj[j]->getSize() / 2.f;
						maxY1 = bulletObj[j]->getY() + bulletObj[j]->getSize() / 2.f;

						if (CollisionRect(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1)) {
							buildingObj[i]->SetDamage(bulletObj[j]->getLife());
							bulletObj[j]->SetLife(0.f);
						}
					}
				}
			}
		}
	}

	// team1 character and team2 arrow
	for (int i = 0; i < MAX_OBJ_COUNT; i++) {
		if (actorObj[i] != NULL) {
			for (int j = 0; j < MAX_OBJ_COUNT; j++) {
				if (actorObj[j] != NULL && actorObj[i] != NULL) {
					if ((actorObj[i]->getType() == OBJECT_CHARACTER && actorObj[i]->getTeam() == TEAM1) && (actorObj[j]->getType() == OBJECT_ARROW && actorObj[j]->getTeam() == TEAM2)) {
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
								actorObj[j]->SetLife(0.f);
							}
						}
					}
				}
			}
		}
	}

	// team2 character and team1 arrow
	for (int i = 0; i < MAX_OBJ_COUNT; i++) {
		if (actorObj[i] != NULL) {
			for (int j = 0; j < MAX_OBJ_COUNT; j++) {
				if (actorObj[j] != NULL && actorObj[i] != NULL) {
					if ((actorObj[i]->getType() == OBJECT_CHARACTER && actorObj[i]->getTeam() == TEAM2) && (actorObj[j]->getType() == OBJECT_ARROW && actorObj[j]->getTeam() == TEAM1)) {
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
								actorObj[j]->SetLife(0.f);
							}
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