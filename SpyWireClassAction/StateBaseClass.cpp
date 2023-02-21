#include "Play.h"
#include "StateBaseClass.h"
#include "StateAppear.h"
#include "StatePlay.h"
#include "StateHalt.h"
#include "StateDead.h"

void StateBaseClass::SwitchStates(Agent8State newState)
{
	Agent8* player = (Agent8*)GameObjectClass::GetPlayer();

	switch (newState)
	{
	case STATE_APPEAR:
		player->SetNextStatePointer(new StateAppear);
		break;

	case STATE_PLAY:
		player->SetNextStatePointer(new StatePlay);
		break;

	case STATE_HALT:
		player->SetNextStatePointer(new StateHalt);
		break;

	case STATE_DEAD:
		player->SetNextStatePointer(new StateDead);
		break;

	default:
		break;
	}
	player->GetNextStatePointer()->m_state = newState;
	m_destroy = true;
}