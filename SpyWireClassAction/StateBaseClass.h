#pragma once
#include "Agent8.h"

// We won't make this base class a pure virtual class as we will want to construct it in the MainGame to store each of the children states in the same pointer.
class StateBaseClass
	: public GameObjectClass
{
public:
	StateBaseClass() : GameObjectClass() {};
	virtual ~StateBaseClass() {};

	virtual void Update() {};
	static void SwitchStates(Agent8State newState);

	static Agent8State GetStateType() { return s_state; };

protected:
	static Agent8State s_state; // <-- used to tell the game state from anywhere.
private:
	static StateBaseClass* s_pStatePointer; // <-- this is only used to avoid searching for each state so shouldn't be used outside of this class
};

