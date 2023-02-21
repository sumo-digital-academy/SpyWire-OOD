#include "Play.h"
#include "Laser.h"

void Laser::Update()
{
	UpdateMovement();
	CollisionUpdateLoop();
	if (IsOffDisplay())
		m_destroy = true;
}

void Laser::CollisionUpdateLoop()
{
	std::vector<GameObjectClass*> collsionCheckList = GetAllObjectsOfType(TYPE_TOOL);
	for (int i = 0; i < collsionCheckList.size(); i++)
	{
		if (collsionCheckList[i] != nullptr && CollisionTest(this, collsionCheckList[i]))
		{
			collsionCheckList[i]->Destroy();
			m_destroy = true;
			*s_pScore += 100; 
		}
	}

	collsionCheckList.erase(collsionCheckList.begin(), collsionCheckList.end()); // erase everything in the list
	collsionCheckList = GetAllObjectsOfType(TYPE_COIN);
	for (int i = 0; i < collsionCheckList.size(); i++)
	{
		if (collsionCheckList[i] != nullptr && CollisionTest(this, collsionCheckList[i]))
		{
			collsionCheckList[i]->Destroy();
			m_destroy = true;
			Play::PlayAudio("error");
			*s_pScore -= 300; 
		}
	}

	if (*s_pScore < 0)
		*s_pScore = 0;
}