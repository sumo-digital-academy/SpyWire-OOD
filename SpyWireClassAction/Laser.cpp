#include "Play.h"
#include "Laser.h"
#include "GameObjectManager.h"
#include "Agent8.h"

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
			((Agent8*)GameObjectManager::GetPlayer(0))->AddScore(100);
		}
	}

 	int numberOfObjects = GameObjectManager::GetAllObjectsOfType(TYPE_COIN, m_collsionCheckList); // this function will erase everything in the list

	if (numberOfObjects > 0)
	{
		for (int i = 0; i < m_collsionCheckList.size(); i++)
		{
			if (m_collsionCheckList[i] != nullptr && CollisionTest(this, m_collsionCheckList[i]))
			{
				m_collsionCheckList[i]->Destroy();
				m_destroy = true;
				Play::PlayAudio("error");
				((Agent8*)GameObjectManager::GetPlayer(0))->AddScore(-300);
			}
		}

		if (((Agent8*)GameObjectManager::GetPlayer(0))->GetScore() < 0)
			((Agent8*)GameObjectManager::GetPlayer(0))->ResetScore();
	}
}