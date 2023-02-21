#include "Play.h"
#include "StateBaseClass.h"
#include "Agent8.h"

// Core states
#include "StateAppear.h"
#include "StatePlay.h"
#include "StateHalt.h"
#include "StateDead.h"

Agent8::Agent8(GameObjectType objType, Point2f position, std::string spriteName)
	: GameObjectClass(objType, position, spriteName)
{
	// as there should only be a single player using this constructor we can set the player in the base class to equal this
	GameObjectClass::SetPlayer(this);

	m_state = STATE_APPEAR;
	m_pCurrentState = new StateAppear; // calling the default constructor for the StateAppear
}

Agent8::~Agent8()
{
	if (m_pCurrentState != nullptr)
	{
		delete m_pCurrentState;
	}

	if (m_pNextState != nullptr)
	{
		delete m_pNextState;
	}
}

void Agent8::Update()
{
	m_pCurrentState->Update();

	UpdateMovement();

	if (m_state != STATE_APPEAR && m_state != STATE_DEAD)
	{
		if (IsLeavingDisplay())
		{
			m_position = m_oldPosition;
		}
	}

	UpdateAnimation();

	if (m_pCurrentState->CheckDestroy())
		SwitchStates();

	Play::DrawLine({ m_position.x, 0 }, m_position, Play::cWhite);
}

void Agent8::SwitchStates()
{
	if (m_pCurrentState != nullptr)
		delete m_pCurrentState;

	m_pCurrentState = m_pNextState;
	m_pNextState = nullptr;

	m_state = m_pCurrentState->GetStateType();
}

void Agent8::SetNextStatePointer(StateBaseClass* nextState) 
{
	if (m_pNextState != nullptr)
		delete m_pNextState;

	m_pNextState = nextState; 
};
