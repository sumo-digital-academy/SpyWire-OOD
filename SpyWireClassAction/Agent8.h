#pragma once
#include "GameObjectClass.h"

class StateBaseClass; // forward declare StateBaseClass to avoid including it in the head causing a #include loop

class Agent8
	: public GameObjectClass
{
public:
	Agent8() : GameObjectClass() {}; // default constructor
	Agent8(GameObjectType objType, Point2f position, std::string spriteName);
	virtual ~Agent8();

	void Update() override;

	StateBaseClass* GetStatePointer() { return m_pCurrentState; };
	Agent8State GetStateType() { return m_state; };
	void SetStateType(Agent8State newState) { m_state = newState; };
	StateBaseClass* GetNextStatePointer() { return m_pNextState; };
	void SetNextStatePointer(StateBaseClass* nextState);

	void SwitchStates();

protected:
	Agent8State m_state{ Agent8State::STATE_APPEAR }; // <-- used to tell the state as to avoid a total code rewrite.
	StateBaseClass* m_pCurrentState{ nullptr }; // stores a pointer to the current state
	StateBaseClass* m_pNextState{ nullptr }; // stores a pointer to the next state (m_ - member variable, p - pointer)
private:
};

