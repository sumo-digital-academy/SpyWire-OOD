#include "Play.h"
#include "Tools.h"
#include "Agent8.h"
#include "StateBaseClass.h"

void Tools::Update()
{
	Agent8* player = (Agent8*)s_pPlayer; // This will allow us to avoid type casting the player every time we need them.

	if (player->GetStateType() != STATE_DEAD && CollisionTest(this, player))
	{
		Play::StopAudioLoop("music");
		Play::PlayAudio("die");

		player->GetStatePointer()->SwitchStates(STATE_DEAD);
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