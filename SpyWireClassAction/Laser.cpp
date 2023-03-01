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
			m_pParentPlayer->AddScore(100);
		}
	}

 	int numberOfObjects = GameObjectManager::GetAllObjectsOfType(TYPE_COIN, m_collsionCheckList); // this function will erase everything in the list before adding to it

	if (numberOfObjects > 0)
	{
		for (int i = 0; i < m_collsionCheckList.size(); i++)
		{
			if (m_collsionCheckList[i] != nullptr && CollisionTest(this, m_collsionCheckList[i]))
			{
				m_collsionCheckList[i]->Destroy();
				m_destroy = true;
				Play::PlayAudio("error");
				m_pParentPlayer->AddScore(-300);
			}
		}

		if (m_pParentPlayer->GetScore() < 0)
			m_pParentPlayer->ResetScore();
	}
}