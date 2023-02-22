#include "Play.h"
#include "StateBaseClass.h"
#include "StateAppear.h"
#include "StatePlay.h"
#include "StateHalt.h"
#include "StateDead.h"

Agent8State StateBaseClass::s_state = Agent8State::STATE_APPEAR;
StateBaseClass* StateBaseClass::s_pStatePointer = new StateAppear;

void StateBaseClass::SwitchStates(Agent8State newState)
{
	Agent8* player = (Agent8*)GameObjectClass::GetPlayer();

	switch (newState)
	{
	case STATE_APPEAR:
		s_pStatePointer->Destroy(); 
		s_pStatePointer = new StateAppear;
		s_state = STATE_APPEAR;
		break;

	case STATE_PLAY:
		s_pStatePointer->Destroy(); 
		s_pStatePointer = new StatePlay;
		s_state = STATE_PLAY;
		break;

	case STATE_HALT:
		s_pStatePointer->Destroy(); 
		s_pStatePointer = new StateHalt;
		s_state = STATE_HALT;
		break;

	case STATE_DEAD:
		s_pStatePointer->Destroy();
		s_pStatePointer = new StateDead;
		s_state = STATE_DEAD;
		break;

	default:
		break;
	}
}