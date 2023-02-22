#include "Play.h"
#include "Agent8.h"
#include "StateBaseClass.h"
#include "GameObjectManager.h"

Agent8::Agent8(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName)
	: GameObjectClass(objType, position, velocity, spriteName)
{
	// as there should only be a single player using this constructor we can set the player in the base class to equal this
	GameObjectManager::SetPlayer(this);
}

void Agent8::Update()
{
	UpdateMovement();

	StateBaseClass::StateUpdate(this);

	if (StateBaseClass::GetStateType() != STATE_APPEAR && StateBaseClass::GetStateType() != STATE_DEAD)
	{
		if (IsLeavingDisplay())
		{
			m_position = m_oldPosition;
		}
	}

	UpdateAnimation();

	Play::DrawLine({ m_position.x, 0 }, m_position, Play::cWhite);
}