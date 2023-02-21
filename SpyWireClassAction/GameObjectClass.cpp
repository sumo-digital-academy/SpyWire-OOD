#include "Play.h"
#include "GameObjectClass.h"

std::vector<GameObjectClass*> GameObjectClass::s_vpGameObjectList; // Must manually initialize all static variables within a class.
GameObjectClass* GameObjectClass::s_pPlayer;
int* GameObjectClass::s_pScore;

GameObjectClass::GameObjectClass(GameObjectType objType, Point2f position, std::string spriteName)
{
	m_type = objType;

	m_spriteName = spriteName;
	m_spriteID = PlayGraphics::Instance().GetSpriteId(m_spriteName.c_str()); // .c_str turns a string into a const char*
	m_frame = 1;
	m_position = position;

	// The sprite starts in the top left pixel so we need to divide the width and the height to get them to align with the center
	m_spriteWidth = Play::GetSpriteWidth(m_spriteID) / 2;
	m_spriteHeight = Play::GetSpriteHeight(m_spriteID) / 2;
	m_radius = m_spriteWidth; // Auto setting each object's radius to be their sprite width - should find a better (box orientated) collision method.

	s_vpGameObjectList.push_back(this); // <-- this will add all objects that use this constructor to the list of GameObjects
}

void GameObjectClass::UpdateAll()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++) // loop through each object in the list
	{
		if (s_vpGameObjectList[i]->GetObjectType() != TYPE_DESTROYED)
		{
			// and call their unique updates
			s_vpGameObjectList[i]->Update();
		}
	}
}

void GameObjectClass::RenderAll()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++) // loop through each object in the list
	{
		// and draw them using their sprite name
		if (s_vpGameObjectList[i]->GetRender())
		{
			GameObjectClass& obj = *s_vpGameObjectList[i]; // making a reference as to avoid typing out s_vpGameObjectList[i] each time we need it in the loop.
			int frame = static_cast<int>(obj.m_frame); // due to obj_frame being a float we will cast it to a int to get rid of the decimals
			Play::DrawSpriteRotated(obj.m_spriteName.c_str(), obj.m_position, frame, obj.m_rotation);
		}
	}
}

void GameObjectClass::DeleteAll()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i) // We are deleting every element in the list so no need to increase i as the vector will shrink the list as we delete
	{
		delete s_vpGameObjectList[i];
		s_vpGameObjectList.erase(s_vpGameObjectList.begin());
	}
}

void GameObjectClass::CleanUp()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->m_destroy) // if m_destroy == true
		{
			delete s_vpGameObjectList[i];
			s_vpGameObjectList.erase(find(s_vpGameObjectList.begin(), s_vpGameObjectList.end(), s_vpGameObjectList[i]));
			i--; // as we delete the vector array will move all elements backwards so we need to move i back by one
		}
	}
}

void GameObjectClass::SetSpriteName(std::string spriteName, float animationSpeed) {
	m_spriteName = spriteName;
	m_spriteID = PlayGraphics::Instance().GetSpriteId(m_spriteName.c_str());
	m_animationSpeed = animationSpeed;
};

bool GameObjectClass::CollisionTest(GameObjectClass* objA, GameObjectClass* objB)
{
	//Don't collide with noObject
	if (objA->m_type == -1 || objB->m_type == -1)
		return false;

	int xDiff = int(objA->m_position.x - objA->m_spriteWidth) - int(objB->m_position.x - objB->m_spriteWidth);
	int yDiff = int(objA->m_position.y + objA->m_spriteHeight) - int(objB->m_position.y + objB->m_spriteHeight);
	int radii = objB->m_radius + objA->m_radius;

	// Game programmers don't do square root!
	return((xDiff * xDiff) + (yDiff * yDiff) < radii * radii);
}

bool GameObjectClass::IsLeavingDisplay()
{
	extern int DISPLAY_HEIGHT;
	extern int DISPLAY_WIDTH;

	if (m_position.x - m_spriteWidth < 0 || m_position.x + m_spriteWidth > DISPLAY_WIDTH)
		return true;

	if (m_position.y - m_spriteHeight < 0 || m_position.y + m_spriteHeight > DISPLAY_HEIGHT)
		return true;

	return false;
}

bool GameObjectClass::IsLeavingDisplay(bool vertical, bool horizontal)
{
	extern int DISPLAY_HEIGHT;
	extern int DISPLAY_WIDTH;

	if (vertical && horizontal)
	{
		if ((m_position.x - m_spriteWidth < 0 || m_position.x + m_spriteWidth > DISPLAY_WIDTH)
			&& (m_position.y - m_spriteHeight < 0 || m_position.y + m_spriteHeight > DISPLAY_HEIGHT))
		{
			return true;
		}

	}

	if (horizontal)
	{
		if (m_position.x - m_spriteWidth < 0 || m_position.x + m_spriteWidth > DISPLAY_WIDTH)
			return true;
	}

	if (vertical)
	{
		if (m_position.y - m_spriteHeight < 0 || m_position.y + m_spriteHeight > DISPLAY_HEIGHT)
			return true;
	}

	return false;
}

bool GameObjectClass::IsOffDisplay()
{
	extern int DISPLAY_HEIGHT;
	extern int DISPLAY_WIDTH;

	if (m_position.x - m_spriteWidth < 0 - (m_spriteWidth * 2) || m_position.x + m_spriteWidth > (DISPLAY_WIDTH + m_spriteWidth * 2))
		return true;

	if (m_position.y - m_spriteHeight < 0 - (m_spriteHeight * 2) || m_position.y + m_spriteHeight > DISPLAY_HEIGHT + (m_spriteHeight * 2))
		return true;

	return false;
}

void GameObjectClass::UpdateMovement()
{
	m_rotation += m_rotationSpeed;
	m_oldPosition = m_position;
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void GameObjectClass::Respawn()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->m_type == TYPE_TOOL)
			s_vpGameObjectList[i]->Destroy();
	}
}

std::vector<GameObjectClass*> GameObjectClass::GetAllObjectsOfType(GameObjectType objType)
{
	std::vector<GameObjectClass*> listOfObjects{ nullptr };
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->m_type == objType)
		{
			listOfObjects.push_back(s_vpGameObjectList[i]);
		}
	}

	return listOfObjects;
}

void GameObjectClass::UpdateAllDestroyed()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++) // loop through each object in the list
	{
		if (s_vpGameObjectList[i]->GetObjectType() == TYPE_DESTROYED)
		{
			s_vpGameObjectList[i]->SetAnimationSpeed(0.2f);
			s_vpGameObjectList[i]->UpdateMovement();
			s_vpGameObjectList[i]->UpdateAnimation();

			int frame = s_vpGameObjectList[i]->GetFrame();
			if (frame % 2)
			{
				s_vpGameObjectList[i]->SetRender(true);
			}
			else
			{
				s_vpGameObjectList[i]->SetRender(false);
			}

			if (s_vpGameObjectList[i]->IsOffDisplay() || frame >= 10)
  				s_vpGameObjectList[i]->Destroy();
		}
	}
}

void GameObjectClass::Destroy()
{
	if (m_type != TYPE_DESTROYED)
	{
		m_frame = 0;
		m_frameTimer = 0;
		m_type = TYPE_DESTROYED;
	}
	else
	{
		m_destroy = true;
	}
}

void GameObjectClass::UpdateAnimation()
{
	m_frameTimer += m_animationSpeed;

	if (m_frameTimer >= 1)
	{
		m_frame++;
		m_frameTimer = 0;
	}
}