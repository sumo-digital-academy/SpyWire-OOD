#include "Play.h"
#include "Star.h"

Star::Star(GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName) 
	: GameObjectClass(objType, position, velocity, spriteName) 
{
	m_rotation = 0.1f;
	m_acceleration = { 0.0f, 0.5f };
}

void Star::Update()
{
	UpdateMovement();
	if (IsOffDisplay())
		m_destroy = true;
}