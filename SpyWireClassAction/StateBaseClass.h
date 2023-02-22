#pragma once
enum Agent8State // <- copyed these here as there is no header to include for them - this will allow me to avoid #including the states in each other, as can be seen in SwitchStates(StateBaseClass* newState).
{
	STATE_APPEAR = 0,
	STATE_HALT,
	STATE_PLAY,
	STATE_DEAD,
};

class Agent8; // This is used to avoid needing to #include "Agent8" in every file that wants to use StateBaseClass (eg in Coin.cpp)

class StateBaseClass
{
public:
	StateBaseClass() {};
	virtual ~StateBaseClass() {};

	static void StateUpdate(Agent8* player) { s_pStatePointer->Update(player); };
	static void SwitchStates(Agent8State newState);
	static void DestroyEnd() { delete s_pStatePointer; } // ONLY CALL THIS AT THE END OF THE GAME, else you will get a horrible memory access violation, this is to avoid memory leaks.
	static Agent8State GetStateType() { return s_state; };

	void Destroy() { delete this; }; // When straight up deleting memory make sure there are no traces of it in the code (eg pointers to the deleted memory)

protected:
	virtual void Update(Agent8* player) {}; // Protected as we want it to be inherited but never used directly
	static Agent8State s_state; // <-- used to tell the game state from anywhere.
private:
	static StateBaseClass* s_pStatePointer; // <-- this is only used to avoid searching for each state so shouldn't be used outside of this class
};

