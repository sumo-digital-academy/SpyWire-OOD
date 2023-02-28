#pragma once
#include "GameObjectClass.h"

class Agent8;

class Laser :
    public GameObjectClass
{
public:
    Laser(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName) : GameObjectClass(objType, position, velocity, spriteName) {};
    ~Laser() {};

    void Update() override;
    void CollisionUpdateLoop();
    void SetParentPlayerIndex(Agent8* parent) { m_pParentPlayer = parent; };
private:
	std::vector<GameObjectClass*> m_collsionCheckList;
    Agent8* m_pParentPlayer{ nullptr };
};

