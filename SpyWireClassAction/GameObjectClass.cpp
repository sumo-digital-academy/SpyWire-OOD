#include "Play.h"
#include "GameObjectClass.h"
#include "GameObjectManager.h"

//extern std::vector<GameObjectClass*> s_vpGameObjectList;

GameObjectClass::GameObjectClass() 
{ 
	GameObjectManager::s_vpGameObjectList.push_back(this);
}; // default constructor - when you make a GameObject with no parameters


GameObjectClass::GameObjectClass(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName)
{
	m_type = objType;

	m_spriteName = spriteName;
	m_spriteID = PlayGraphics::Instance().GetSpriteId(m_spriteName.c_str()); // .c_str turns a string into a const char*
	m_frame = 1;
	m_position = position;
	m_velocity = velocity;

	// The sprite starts in the top left pixel so we need to divide the width and the height to get them to align with the center
	m_spriteWidth = Play::GetSpriteWidth(m_spriteID) / 2;
	m_spriteHeight = Play::GetSpriteHeight(m_spriteID) / 2;
	m_radius = m_spriteWidth; // Auto setting each object's radius to be their sprite width - should find a better (box orientated) collision method.

	GameObjectManager::s_vpGameObjectList.push_back(this); // <-- this will add all objects that use this constructor to the list of GameObjects
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
	for (int i = 0; i < GameObjectManager::s_vpGameObjectList.size(); i++)
	{
		if (GameObjectManager::s_vpGameObjectList[i]->m_type == TYPE_TOOL)
			GameObjectManager::s_vpGameObjectList[i]->Destroy();
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