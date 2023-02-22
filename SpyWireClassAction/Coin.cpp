#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Coin.h"
#include "Agent8.h"
#include "StateBaseClass.h"
#include "Factory.h"

static constexpr int SPEED = 16;

void Coin::Update()
{
	Agent8* player = (Agent8*)s_pPlayer;
	if (StateBaseClass::GetStateType() != STATE_DEAD && CollisionTest(this, player))
		OnCollision();

	UpdateMovement();
	if (IsOffDisplay())
		m_destroy = true;
}

void Coin::OnCollision()
{
	for (float rad{ 0.25f }; rad < 2.0f; rad += 0.5f)
	{
		GameObjectClass* star = Factory::ReturnCreateObject(TYPE_STAR, GetPlayer()->GetPosition());

		float angle = rad * PLAY_PI;
		star->SetVelocity({ SPEED * sin(angle), SPEED * -cos(angle) });
	}
	*s_pScore += 500; // turn the pointer from a memory address to the int value
	Play::PlayAudio("collect");
	m_destroy = true;
}