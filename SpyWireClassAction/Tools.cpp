#include "Play.h"
#include "Tools.h"
#include "StateBaseClass.h"
#include "GameObjectManager.h"

Tools::Tools(GameObjectType objTypes, Point2f position, Vector2f velocity, std::string sprtieName)
	: GameObjectClass(objTypes, position, velocity, sprtieName)
{
	if (Play::RandomRoll(2) == 1)
	{
		m_spriteID = Play::GetSpriteId("spanner");
		m_velocity = { -4, 0 };
		m_rotationSpeed = 0.1f;
	}
	else
	{
		m_spriteID = Play::GetSpriteId("driver");
		m_velocity = { -8, Play::RandomRollRange(-1, 1) * 6 };
	}
}

void Tools::Update()
{
	if (StateBaseClass::GetStateType() != STATE_DEAD && CollisionTest(this, GameObjectManager::GetPlayer(0)))
	{
		Play::StopAudioLoop("music");
		Play::PlayAudio("die");

		StateBaseClass::SwitchStates(STATE_DEAD);
	}
	UpdateMovement();
	UpdateAnimation();

	if (IsLeavingDisplay(true, false)) // Using a function overload to check only the vertical movements
	{
		m_position = m_oldPosition;
		m_velocity.y *= -1;
	}
	
	if (IsOffDisplay())
	{
		m_destroy = true;
	}
}