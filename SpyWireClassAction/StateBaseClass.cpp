#include "Play.h"
#include "Agent8.h"
#include "StateBaseClass.h"
#include "StateAppear.h"
#include "StatePlay.h"
#include "StateHalt.h"
#include "StateDead.h"

std::vector<StateBaseClass*> StateBaseClass::s_pStatePointerList;

StateBaseClass::StateBaseClass(Agent8* player)
{
	m_pPlayer = player;
	s_pStatePointerList.push_back(this);
}

void StateBaseClass::SwitchStates(Agent8* player, Agent8State newState)
{
	StateBaseClass* currentState = FindPlayerState(*player);
	switch (newState)
	{
	case STATE_APPEAR:
		// Note that it is fine to freely delete the state here as it is not in a list and the pointer is about to be replaces
		s_pStatePointerList.erase(find(s_pStatePointerList.begin(), s_pStatePointerList.end(), currentState));
		delete currentState;
		currentState = new StateAppear(player);
		currentState->m_state = STATE_APPEAR;
		break;

	case STATE_PLAY:
		s_pStatePointerList.erase(find(s_pStatePointerList.begin(), s_pStatePointerList.end(), currentState));
		delete currentState;
		currentState = new StatePlay(player);
		currentState->m_state = STATE_PLAY;
		break;

	case STATE_HALT:
		s_pStatePointerList.erase(find(s_pStatePointerList.begin(), s_pStatePointerList.end(), currentState));
		delete currentState;
		currentState = new StateHalt(player);
		currentState->m_state = STATE_HALT;
		break;

	case STATE_DEAD:
		s_pStatePointerList.erase(find(s_pStatePointerList.begin(), s_pStatePointerList.end(), currentState));
		delete currentState;
		currentState = new StateDead(player);
		currentState->m_state = STATE_DEAD;
		break;

	default:
		break;
	}
}

void StateBaseClass::DestroyAll()
{
	for (int i = 0; i < s_pStatePointerList.size(); i++)
	{
		delete s_pStatePointerList[i];
	}

	s_pStatePointerList.clear();
}

//void StateBaseClass::UpdateAllStates()
//{
//	for (int i = 0; i < s_pStatePointerList.size(); i++)
//		s_pStatePointerList[i]->Update();
//}

Agent8State StateBaseClass::GetStateType(Agent8* player)
{
	for (int i = 0; i < s_pStatePointerList.size(); i++)
	{
		if (s_pStatePointerList[i]->m_pPlayer == player)
		{
			return s_pStatePointerList[i]->m_state;
		}
	}
}

StateBaseClass* StateBaseClass::FindPlayerState(const Agent8& player)
{
	for (int i = 0; i < s_pStatePointerList.size(); i++)
	{
		if (s_pStatePointerList[i]->m_pPlayer == &player)
		{
			return s_pStatePointerList[i];
		}
	}
}