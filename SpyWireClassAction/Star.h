#pragma once
#include "GameObjectClass.h"
class Star :
    public GameObjectClass
{
public:
    Star(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName);
    ~Star() {};

    void Update() override;
};

