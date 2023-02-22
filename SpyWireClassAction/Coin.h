#pragma once
#include "GameObjectClass.h"
class Coin :
    public GameObjectClass
{
public:
	Coin(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName) : GameObjectClass(objType, position, velocity, spriteName) { m_rotationSpeed = 0.1f; };
	~Coin() {};

	void Update() override;
	void OnCollision() override;
};

