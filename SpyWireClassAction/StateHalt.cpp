#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "StateHalt.h"


void StateHalt::Update()
{
	GameObjectClass* player = GameObjectClass::GetPlayer();
	player->SetVelocity(player->GetVelocity() * 0.9f);
	
	int maxFrames = PlayGraphics::Instance().GetSpriteFrames(player->GetSpriteID()) - 1;
	if (player->GetFrame() >= maxFrames)
		SwitchStates(STATE_PLAY);
}