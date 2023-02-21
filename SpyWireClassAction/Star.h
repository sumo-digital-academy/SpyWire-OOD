#pragma once
#include "GameObjectClass.h"
class Star :
    public GameObjectClass
{
public:
    Star(GameObjectType objType, Point2f position, std::string spriteName) : GameObjectClass(objType, position, spriteName) {};
    ~Star() {};

    void Update() override;
};

