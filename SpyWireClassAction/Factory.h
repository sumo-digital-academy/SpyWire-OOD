#pragma once
class Factory
{
public:
	static void CreateObject(GameObjectType objType, Point2f pos, Vector2f vel);
	static GameObjectClass* ReturnCreateObject(GameObjectType objType, Point2f pos, Vector2f vel);
};

