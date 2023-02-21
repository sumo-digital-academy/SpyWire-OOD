#pragma once
#include "GameObjectClass.h"
class Fan :
    public GameObjectClass
{
public:
    Fan(GameObjectType objType, Point2f position, std::string spriteName);
    ~Fan() {};

    void Update() override;
};

