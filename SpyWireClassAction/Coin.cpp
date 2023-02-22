#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Coin.h"
#include "StateBaseClass.h"
#include "GameObjectManager.h"

static constexpr int SPEED = 16;

void Coin::Update()
{
	if (StateBaseClass::GetStateType() != STATE_DEAD && CollisionTest(this, GameObjectManager::GetPlayer()))
		OnCollision();

	UpdateMovement();
	if (IsOffDisplay())
		m_destroy = true;
}

void Coin::OnCollision()
{
	for (float rad{ 0.25f }; rad < 2.0f; rad += 0.5f)
	{
		GameObjectClass* star = GameObjectManager::CreateObject(TYPE_STAR, GameObjectManager::GetPlayer()->GetPosition(), { 0, 0 });

		float angle = rad * PLAY_PI;
		star->SetVelocity({ SPEED * sin(angle), SPEED * -cos(angle) });
	}
	*GameObjectManager::GetScorePointer() += 500; // turn the pointer from a memory address to the int value
	Play::PlayAudio("collect");
	m_destroy = true;
}