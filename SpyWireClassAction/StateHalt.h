#pragma once
#include "StateBaseClass.h"
class StateHalt :
    public StateBaseClass
{
public:
    StateHalt() : StateBaseClass() {};
    ~StateHalt() {};

    void Update() override;
};

