#pragma once
#include "GameObjectClass.h"

class StateBaseClass; // forward declare StateBaseClass to avoid including it in the head causing a #include loop

class Agent8
	: public GameObjectClass
{
public:
	Agent8(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName);
	~Agent8() {};

	void Update() override;
	void AddScore(int x) { m_score += x; };
	void ResetScore() {	m_score = 0;};
	int GetScore() { return m_score; };

protected:
private:
	int m_score{ 0 };
};

