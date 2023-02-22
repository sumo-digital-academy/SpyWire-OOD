#include "Play.h"
#include "GameObjectClass.h"
#include "Factory.h"
#include "Agent8.h"
#include "Fan.h"
#include "Coin.h"
#include "Tools.h"
#include "Star.h"
#include "Laser.h"

void Factory::CreateObject(GameObjectType objType, Point2f pos, Vector2f vel)
{
	switch (objType)
	{
	case TYPE_NULL:
		return;
		break;

	case TYPE_AGENT8:
		new Agent8(TYPE_AGENT8, pos, vel, "agent8");
		break;

	case TYPE_FAN:
	{
		Fan* f = new Fan(TYPE_FAN, pos, vel, "fan");
		break;
	}

	case TYPE_COIN:
	{
		Coin* c = new Coin(TYPE_COIN, pos, vel, "coin");
		break;
	}

	case TYPE_TOOL:
	{
		Tools* t = nullptr;

		// Note that due to there being a 50% chance of ever a spanner or driver we will set each specific type here not in the constructor
		// This will allow for the user to create a specific type of tool should they need to later on.
		if (Play::RandomRoll(2) == 1)
		{
			Tools* t = new Tools(TYPE_TOOL, pos, vel, "spanner");
			t->SetRotationSpeed(0.1f);
		}
		else
		{
			Tools* t = new Tools(TYPE_TOOL, pos, vel, "driver");
			t->SetVelocity({ -8, Play::RandomRollRange(-1, 1) * 6 });
		}

		break;
	}

	case TYPE_STAR:
	{
		Star* s = new Star(TYPE_STAR, pos, vel, "star");
		break;
	}

	case TYPE_LASER:
	{
		Laser* l = new Laser(TYPE_LASER, pos, vel, "laser");
		break;
	}

	default:
		break;
	}
}

GameObjectClass* Factory::ReturnCreateObject(GameObjectType objType, Point2f pos, Vector2f vel)
{
	switch (objType)
	{
	case TYPE_NULL:
		return nullptr;
		break;

	case TYPE_AGENT8:
		return new Agent8(TYPE_AGENT8, pos, vel, "agent8");
		break;

	case TYPE_FAN:
	{
		return new Fan(TYPE_FAN, pos, vel, "fan");
		break;
	}

	case TYPE_COIN:
	{
		return new Coin(TYPE_COIN, pos, vel, "coin");
		break;
	}

	case TYPE_TOOL:
	{
		Tools* t = nullptr;

		if (Play::RandomRoll(2) == 1)
		{
			Tools* t = new Tools(TYPE_TOOL, pos, vel, "spanner");
			t->SetVelocity({ -4, 0 });
			t->SetRotationSpeed(0.1f);
		}
		else
		{
			Tools* t = new Tools(TYPE_TOOL, pos, vel, "driver");
			t->SetVelocity({ -8, Play::RandomRollRange(-1, 1) * 6 });
		}

		return t;
		break;
	}

	case TYPE_STAR:
	{
		return new Star(TYPE_STAR, pos, vel, "star");
		break;
	}

	case TYPE_LASER:
	{
		return new Laser(TYPE_LASER, pos, vel, "laser");
		break;
	}

	default:
		return nullptr;
	}
}