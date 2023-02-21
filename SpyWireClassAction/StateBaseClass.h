#pragma once
#include "Agent8.h"

// We won't make this base class a pure virtual class as we will want to construct it in the MainGame to store each of the children states in the same pointer.
class StateBaseClass
	: public Agent8
{
public:
	StateBaseClass() : Agent8() {};
	virtual ~StateBaseClass() {};

	virtual void Update() {};
	void SwitchStates(Agent8State newState);

protected:
private:
};

