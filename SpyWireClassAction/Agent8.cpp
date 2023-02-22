#include "Play.h"
#include "StateBaseClass.h"
#include "Agent8.h"

//// Core states
//#include "StateAppear.h"
//#include "StatePlay.h"
//#include "StateHalt.h"
//#include "StateDead.h"

Agent8::Agent8(GameObjectType objType, Point2f position, std::string spriteName)
	: GameObjectClass(objType, position, spriteName)
{
	// as there should only be a single player using this constructor we can set the player in the base class to equal this
	GameObjectClass::SetPlayer(this);
}

void Agent8::Update()
{
	UpdateMovement();

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