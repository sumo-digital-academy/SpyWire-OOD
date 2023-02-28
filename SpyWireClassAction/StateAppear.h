#pragma once
#include "StateBaseClass.h"
class StateAppear :
    public StateBaseClass
{
public:
    StateAppear(Agent8* player) : StateBaseClass(player) {};
    ~StateAppear() {};

    void Update(Agent8* player) override;
protected:
private:
};

