#pragma once
#include "GameObjectClass.h"

class Tools
	: public GameObjectClass
{
public:
	Tools(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName)
		: GameObjectClass(objType, position, velocity, spriteName) {};

	~Tools() {};

	void Update() override;
};

