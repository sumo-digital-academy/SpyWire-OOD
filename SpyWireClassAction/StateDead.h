#pragma once
#include "StateBaseClass.h"
class StateDead :
    public StateBaseClass
{
public:
    StateDead(Agent8* player) : StateBaseClass(player) {};
    ~StateDead() {};

    void Update(Agent8* player) override;
};

