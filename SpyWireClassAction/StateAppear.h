#pragma once
#include "StateBaseClass.h"
class StateAppear :
    public StateBaseClass
{
public:
    StateAppear() : StateBaseClass() {};
    ~StateAppear() {};

    void Update() override;
protected:
private:
};

