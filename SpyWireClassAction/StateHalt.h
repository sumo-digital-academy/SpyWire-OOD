#pragma once
#include "StateBaseClass.h"
class StateHalt :
    public StateBaseClass
{
public:
    StateHalt() : StateBaseClass() {};
    ~StateHalt() {};

    void Update(Agent8* player) override;
};

