#pragma once
#include "StateBaseClass.h"
class StateHalt :
    public StateBaseClass
{
public:
    StateHalt(Agent8* player) : StateBaseClass(player) {};
    ~StateHalt() {};

    void Update(Agent8* player) override;
};

