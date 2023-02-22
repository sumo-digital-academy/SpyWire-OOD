#pragma once
#include "GameObjectClass.h"
class Laser :
    public GameObjectClass
{
public:
    Laser(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName) : GameObjectClass(objType, position, velocity, spriteName) {};
    ~Laser() {};

    void Update() override;
    void CollisionUpdateLoop();
};

