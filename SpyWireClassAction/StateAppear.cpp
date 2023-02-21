#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "StateAppear.h"
#include "StatePlay.h"

extern int DISPLAY_HEIGHT;

void StateAppear::Update()
{
	GameObjectClass* player = GameObjectClass::GetPlayer();

	player->SetVelocity({ 0, 12 });
	player->SetAcceleration({ 0, 0.5f });
	player->SetSpriteName("agent8_fall", 0.0f);
	player->SetRotation(0);

	if (player->GetPosition().y >= DISPLAY_HEIGHT / 3)
		SwitchStates(STATE_PLAY);
}