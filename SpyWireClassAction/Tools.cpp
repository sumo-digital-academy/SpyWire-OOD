#include "Play.h"
#include "Tools.h"
#include "StateBaseClass.h"

void Tools::Update()
{
	if (StateBaseClass::GetStateType() != STATE_DEAD && CollisionTest(this, s_pPlayer))
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