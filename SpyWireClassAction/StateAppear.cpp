#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "Agent8.h"
#include "StateAppear.h"
#include "StatePlay.h"

extern int DISPLAY_HEIGHT;

void StateAppear::Update(Agent8* player)
{
	player->SetVelocity({ 0, 12 });
	player->SetAcceleration({ 0, 0.5f });
	player->SetSprite("agent8_fall", 0.0f);
	player->SetRotation(0);

	if (player->GetPosition().y >= DISPLAY_HEIGHT / 3)
		SwitchStates(STATE_PLAY);
}