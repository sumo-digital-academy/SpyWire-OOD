#pragma once
enum Agent8State // <- By having the states here anything that knows (#includes) this class will know about the states as well
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
	StateBaseClass(Agent8* player);
	virtual ~StateBaseClass() {};

	//static void UpdateAllStates();
	static void DestroyAll(); // ONLY CALL THIS AT THE END OF THE GAME, else you will get a horrible memory leak.
	static void SwitchStates(Agent8* player, Agent8State newState);
	static Agent8State GetStateType(Agent8* player);
	static StateBaseClass* FindPlayerState(const Agent8& player);
	
	virtual void Update(Agent8* player) {}; // Protected as we want it to be inherited but never used directly

protected:
	Agent8State m_state{ STATE_APPEAR }; // <-- used to tell the game state from anywhere.
	Agent8* m_pPlayer{ nullptr };
private:
	static std::vector<StateBaseClass*> s_pStatePointerList; // <-- this is only used to avoid searching for each state so shouldn't be used outside of this class
};

