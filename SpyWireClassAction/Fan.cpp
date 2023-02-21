#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "Fan.h"
#include "Factory.h"

Fan::Fan(GameObjectType objType, Point2f pos, std::string spriteName)
	: GameObjectClass(objType, pos, spriteName)
{

}

void Fan::Update()
{
	if (Play::RandomRoll(50) == 50)
	{
		Factory::CreateObject(TYPE_TOOL, m_position);
		Play::PlayAudio("tool");
	}

	if (Play::RandomRoll(150) == 1)
	{
		Factory::CreateObject(TYPE_COIN, m_position);
	}

	UpdateMovement();

	if (IsLeavingDisplay())
	{
		m_position = m_oldPosition;
		m_velocity.y *= -1;
	}
}