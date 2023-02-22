#pragma once
#include "StateBaseClass.h"
class StateAppear :
    public StateBaseClass
{
public:
    StateAppear() : StateBaseClass() {};
    ~StateAppear() {};

    void Update(Agent8* player) override;
protected:
private:
};

