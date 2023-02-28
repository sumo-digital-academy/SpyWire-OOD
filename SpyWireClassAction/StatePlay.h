#pragma once
#include "StateBaseClass.h"
class StatePlay :
    public StateBaseClass
{
public:
    StatePlay(Agent8* player) : StateBaseClass(player) {};
    ~StatePlay() {};

    void Update(Agent8* player) override;
};