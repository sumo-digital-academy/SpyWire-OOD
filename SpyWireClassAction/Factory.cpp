#include "Play.h"
#include "GameObjectClass.h"
#include "Factory.h"
#include "Agent8.h"
#include "Fan.h"
#include "Coin.h"
#include "Tools.h"
#include "Star.h"
#include "Laser.h"

void Factory::CreateObject(GameObjectType objType, Point2f pos)
{
	switch (objType)
	{
	case TYPE_NULL:
		return;
		break;

	case TYPE_AGENT8:
		new Agent8(TYPE_AGENT8, pos, "agent8");
		break;

	case TYPE_FAN:
	{
		Fan* f = new Fan(TYPE_FAN, pos, "fan");
		f->SetVelocity({ 0,3 });
		f->SetAnimationSpeed(1.0f);
		break;
	}

	case TYPE_COIN:
	{
		Coin* c = new Coin(TYPE_COIN, pos, "coin");
		c->SetVelocity({ -3, 0 });
		c->SetRotationSpeed(0.1f);
		break;
	}

	case TYPE_TOOL:
	{
		Tools* t = nullptr;

		if (Play::RandomRoll(2) == 1)
		{
			Tools* t = new Tools(TYPE_TOOL, pos, "spanner");
			t->SetVelocity({ -4, 0 });
			t->SetRotationSpeed(0.1f);
		}
		else
		{
			Tools* t = new Tools(TYPE_TOOL, pos, "driver");
			t->SetVelocity({ -8, Play::RandomRollRange(-1, 1) * 6 });
		}

		break;
	}

	case TYPE_STAR:
	{
		Star* s = new Star(TYPE_STAR, pos, "star");
		s->SetRotation(0.1f);
		s->SetAcceleration({ 0.0f, 0.5f });

		break;
	}

	case TYPE_LASER:
	{
		Laser* l = new Laser(TYPE_LASER, pos, "laser");
		l->SetVelocity({ 32, 0 });

		break;
	}

	default:
		break;
	}
}

GameObjectClass* Factory::ReturnCreateObject(GameObjectType objType, Point2f pos)
{
	switch (objType)
	{
	case TYPE_NULL:
		return nullptr;
		break;

	case TYPE_AGENT8:
		return new Agent8(TYPE_AGENT8, pos, "agent8");
		break;

	case TYPE_FAN:
	{
		Fan* f = new Fan(TYPE_FAN, pos, "fan");
		f->SetVelocity({ 0,3 });
		f->SetAnimationSpeed(1.0f);
		return f;
		break;
	}

	case TYPE_COIN:
	{
		Coin* c = new Coin(TYPE_COIN, pos, "coin");
		c->SetVelocity({ -3, 0 });
		c->SetRotationSpeed(0.1f);
		return c;
		break;
	}

	case TYPE_TOOL:
	{
		Tools* t = nullptr;

		if (Play::RandomRoll(2) == 1)
		{
			Tools* t = new Tools(TYPE_TOOL, pos, "spanner");
			//obj_tool.radius = 100;
			t->SetVelocity({ -4, 0 });
			t->SetRotationSpeed(0.1f);
		}
		else
		{
			Tools* t = new Tools(TYPE_TOOL, pos, "driver");
			t->SetVelocity({ -8, Play::RandomRollRange(-1, 1) * 6 });
		}

		return t;
		break;
	}

	case TYPE_STAR:
	{
		Star* s = new Star(TYPE_STAR, pos, "star");
		s->SetRotation(0.1f);
		s->SetAcceleration({ 0.0f, 0.5f });

		return s;
		break;
	}

	case TYPE_LASER:
	{
		Laser* l = new Laser(TYPE_LASER, pos, "laser");
		l->SetVelocity({ 32, 0 });

		return l;
		break;
	}

	default:
		return nullptr;
	}
}