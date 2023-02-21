#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "StateDead.h"

void StateDead::Update()
{
	GameObjectClass* player = GameObjectClass::GetPlayer();

	player->SetAcceleration({ -0.3f , 0.5f });
	player->SetRotation(player->GetRotation() + 0.25f);

	if (Play::KeyPressed(VK_SPACE) == true)
	{
		SwitchStates(STATE_APPEAR);
		player->SetPosition({ 115, 0 });
		player->SetVelocity({ 0, 0 });
		player->SetFrame(0);
		Play::StartAudioLoop("music");
		Respawn();
		*s_pScore = 0;
		for (int id_obj : Play::CollectGameObjectIDsByType(TYPE_TOOL)) // remove this later for classes
			Play::GetGameObject(id_obj).type = TYPE_DESTROYED;
	}
}