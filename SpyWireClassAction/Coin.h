#pragma once
#include "GameObjectClass.h"
class Coin :
    public GameObjectClass
{
public:
	Coin(GameObjectType objType, Point2f position, std::string spriteName) : GameObjectClass(objType, position, spriteName) {};
	~Coin() {};

	void Update() override;
	void OnCollision() override;
};

