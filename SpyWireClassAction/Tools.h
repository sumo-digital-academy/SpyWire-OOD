#pragma once
#include "GameObjectClass.h"

class Tools
	: public GameObjectClass
{
public:
	Tools(GameObjectType objType, Point2f position, std::string spriteName)
		: GameObjectClass(objType, position, spriteName) {};

	~Tools() {};

	void Update() override;
};

