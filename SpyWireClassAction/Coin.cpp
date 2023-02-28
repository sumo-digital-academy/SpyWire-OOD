#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Coin.h"
#include "StateBaseClass.h"
#include "GameObjectManager.h"
#include "Agent8.h"

static constexpr int SPEED = 16;

void Coin::Update()
{
	std::vector<GameObjectClass*> playerList;
	GameObjectManager::GetAllPlayers(playerList, true);

	for (int i = 0; i < playerList.size(); i++)
	{
		if (StateBaseClass::GetStateType((Agent8*)playerList[i]) != STATE_DEAD && CollisionTest(this, playerList[i]))
			OnCollision(i);
	}

	UpdateMovement();
	if (IsOffDisplay())
		m_destroy = true;
}

void Coin::OnCollision(int playerIndex)
{
	GameObjectClass* player = GameObjectManager::GetPlayer(playerIndex);

	for (float rad{ 0.25f }; rad < 2.0f; rad += 0.5f)
	{
		GameObjectClass* star = GameObjectManager::CreateObject(TYPE_STAR, player->GetPosition(), { 0, 0 });

		float angle = rad * PLAY_PI;
		star->SetVelocity({ SPEED * sin(angle), SPEED * -cos(angle) });
	}
	((Agent8*)player)->AddScore(500); // turn the pointer from a memory address to the int value
	
	Play::PlayAudio("collect");
	m_destroy = true;
}