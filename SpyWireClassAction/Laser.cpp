#include "Play.h"
#include "Laser.h"
#include "GameObjectManager.h"

void Laser::Update()
{
	UpdateMovement();
	CollisionUpdateLoop();
	if (IsOffDisplay())
		m_destroy = true;
}

void Laser::CollisionUpdateLoop()
{
	std::vector<GameObjectClass*> collsionCheckList = GameObjectManager::GetAllObjectsOfType(TYPE_TOOL);
	for (int i = 0; i < collsionCheckList.size(); i++)
	{
		if (collsionCheckList[i] != nullptr && CollisionTest(this, collsionCheckList[i]))
		{
			collsionCheckList[i]->Destroy();
			m_destroy = true;
			*GameObjectManager::GetScorePointer() += 100;
		}
	}

	collsionCheckList.erase(collsionCheckList.begin(), collsionCheckList.end()); // erase everything in the list
	collsionCheckList = GameObjectManager::GetAllObjectsOfType(TYPE_COIN);
	for (int i = 0; i < collsionCheckList.size(); i++)
	{
		if (collsionCheckList[i] != nullptr && CollisionTest(this, collsionCheckList[i]))
		{
			collsionCheckList[i]->Destroy();
			m_destroy = true;
			Play::PlayAudio("error");
			*GameObjectManager::GetScorePointer() -= 300;
		}
	}

	if (*GameObjectManager::GetScorePointer() < 0)
		*GameObjectManager::GetScorePointer() = 0;
}