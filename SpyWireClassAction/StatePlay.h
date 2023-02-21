#pragma once
#include "StateBaseClass.h"
class StatePlay :
    public StateBaseClass
{
public:
    StatePlay() : StateBaseClass() {};
    ~StatePlay() {};

    void Update() override;
};