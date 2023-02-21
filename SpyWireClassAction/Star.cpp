#include "Play.h"
#include "Star.h"

void Star::Update()
{
	UpdateMovement();
	if (IsOffDisplay())
		m_destroy = true;
}