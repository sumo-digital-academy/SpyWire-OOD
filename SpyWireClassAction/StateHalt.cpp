#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "Agent8.h"
#include "StateHalt.h"


void StateHalt::Update(Agent8* player)
{
	player->SetVelocity(player->GetVelocity() * 0.9f);
	
	int maxFrames = PlayGraphics::Instance().GetSpriteFrames(player->GetSpriteID()) - 1;
	if (player->GetFrame() >= maxFrames)
		SwitchStates(player, STATE_PLAY);
}