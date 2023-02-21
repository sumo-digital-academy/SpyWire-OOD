#pragma once
#include "GameObjectClass.h"
class Laser :
    public GameObjectClass
{
public:
    Laser(GameObjectType objType, Point2f position, std::string spriteName) : GameObjectClass(objType, position, spriteName) {};
    ~Laser() {};

    void Update() override;
    void CollisionUpdateLoop();
};

