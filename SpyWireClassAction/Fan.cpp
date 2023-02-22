#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "Fan.h"
#include "GameObjectManager.h"

Fan::Fan(GameObjectType objType, Point2f pos, Vector2f velocity, std::string spriteName)
	: GameObjectClass(objType, pos, velocity, spriteName)
{
	m_animationSpeed = 1.0f;
}

void Fan::Update()
{
	if (Play::RandomRoll(50) == 50)
	{
		GameObjectManager::CreateObject(TYPE_TOOL, m_position, { -4, 0 });
		Play::PlayAudio("tool");
	}

	if (Play::RandomRoll(150) == 1)
	{
		GameObjectManager::CreateObject(TYPE_COIN, m_position, { -3, 0 });
	}

	UpdateMovement();

	if (IsLeavingDisplay())
	{
		m_position = m_oldPosition;
		m_velocity.y *= -1;
	}
}