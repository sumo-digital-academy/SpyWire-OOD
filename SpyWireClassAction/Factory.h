#pragma once
class Factory
{
public:
	static GameObjectClass* CreateObject(GameObjectType objType, Point2f pos, Vector2f vel);
};

