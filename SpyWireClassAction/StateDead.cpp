#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "Agent8.h"
#include "StateDead.h"
#include "GameObjectManager.h"

void StateDead::Update(Agent8* player)
{
	player->SetAcceleration({ -0.3f , 0.5f });
	player->SetRotation(player->GetRotation() + 0.25f);

	if (Play::KeyPressed(VK_SPACE) == true)
	{
		SwitchStates(player, STATE_APPEAR);
		player->SetPosition({ 115, 0 });
		player->SetVelocity({ 0, 0 });
		player->SetFrame(0);
		Play::StartAudioLoop("music");
		GameObjectManager::DeleteGameObjectsByType(TYPE_TOOL);
		player->ResetScore();
		for (int id_obj : Play::CollectGameObjectIDsByType(TYPE_TOOL)) // remove this later for classes
			Play::GetGameObject(id_obj).type = TYPE_DESTROYED;
	}
}