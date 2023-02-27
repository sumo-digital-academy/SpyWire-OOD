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
	GameObjectManager::GetAllObjectsOfType(TYPE_TOOL, m_collsionCheckList);

	for (int i = 0; i < m_collsionCheckList.size(); i++)
	{
		if (m_collsionCheckList[i] != nullptr && CollisionTest(this, m_collsionCheckList[i]))
		{
			m_collsionCheckList[i]->Destroy();
			m_destroy = true;
			*GameObjectManager::GetScorePointer() += 100;
		}
	}

	int numberOfObjects = GameObjectManager::GetAllObjectsOfType(TYPE_COIN, m_collsionCheckList); // this function will erase everything in the list

	if (numberOfObjects < 0)
	{
		for (int i = 0; i < m_collsionCheckList.size(); i++)
		{
			if (m_collsionCheckList[i] != nullptr && CollisionTest(this, m_collsionCheckList[i]))
			{
				m_collsionCheckList[i]->Destroy();
				m_destroy = true;
				Play::PlayAudio("error");
				*GameObjectManager::GetScorePointer() -= 300;
			}
		}

		if (*GameObjectManager::GetScorePointer() < 0)
			*GameObjectManager::GetScorePointer() = 0;
	}
}