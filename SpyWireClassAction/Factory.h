#pragma once
class Factory
{
public:
	static void CreateObject(GameObjectType objType, Point2f pos);
	static GameObjectClass* ReturnCreateObject(GameObjectType objType, Point2f pos);
};

