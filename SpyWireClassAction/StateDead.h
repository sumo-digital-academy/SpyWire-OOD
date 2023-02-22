#pragma once
#include "StateBaseClass.h"
class StateDead :
    public StateBaseClass
{
public:
    StateDead() : StateBaseClass() {};
    ~StateDead() {};

    void Update(Agent8* player) override;
};

