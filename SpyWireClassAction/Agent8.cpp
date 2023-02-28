#include "Play.h"
#include "Agent8.h"
#include "StateBaseClass.h"
#include "GameObjectManager.h"
#include "StateAppear.h"

Agent8::Agent8(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName)
	: GameObjectClass(objType, position, velocity, spriteName)
{
	GameObjectManager::AddPlayer(this);
	new StateAppear(this);
}

void Agent8::Update()
{
	//m_state->Update();

	StateBaseClass::FindPlayerState(*this)->Update(this);
	UpdateMovement();

	if (StateBaseClass::GetStateType(this) != STATE_APPEAR && StateBaseClass::GetStateType(this) != STATE_DEAD)
	{
		if (IsLeavingDisplay())
		{
			m_position = m_oldPosition;
		}
	}

	UpdateAnimation();

	Play::DrawLine({ m_position.x, 0 }, m_position, Play::cWhite);
}