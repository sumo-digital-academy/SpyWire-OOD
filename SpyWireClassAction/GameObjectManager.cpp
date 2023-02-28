#include "Play.h"
#include "GameObjectClass.h"
#include "GameObjectManager.h"
#include "Agent8.h"
#include "Fan.h"
#include "Coin.h"
#include "Tools.h"
#include "Star.h"
#include "Laser.h"

std::vector<GameObjectClass*> GameObjectManager::s_vpGameObjectList; // Must manually initialize all static variables within a class.
GameObjectClass* GameObjectManager::s_pPlayer;

GameObjectClass* GameObjectManager::CreateObject(GameObjectType objType, Point2f pos, Vector2f vel)
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
		return new Tools(TYPE_TOOL, pos, vel, "");
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

void GameObjectManager::UpdateAll()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++) // loop through each object in the list
	{
		if (s_vpGameObjectList[i]->GetObjectType() != TYPE_DESTROYED)
		{
			// and call their unique updates
			s_vpGameObjectList[i]->Update();
		}
	}
}

void GameObjectManager::RenderAll()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++) // loop through each object in the list
	{
		// and draw them using their sprite name
		if (s_vpGameObjectList[i]->GetRender())
		{
			GameObjectClass& obj = *s_vpGameObjectList[i]; // making a reference as to avoid typing out s_vpGameObjectList[i] each time we need it in the loop.

			if (obj.GetSpriteID() != -1) // This is to avoid drawing the states which don't have a sprite name 
			{
				int frame = static_cast<int>(obj.GetFrame()); // due to obj_frame being a float we will cast it to a int to get rid of the decimals
				Play::DrawSpriteRotated(obj.GetSpriteID(), obj.GetPosition(), frame, obj.GetRotation(), 1, 1);
			}
		}
	}
}

void GameObjectManager::DeleteAll()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++) // We are deleting every element in the list so no need to increase i as the vector will shrink the list as we delete
	{
		delete s_vpGameObjectList[i];
	}
	s_vpGameObjectList.clear();
}

void GameObjectManager::CleanUp()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->CheckDestroy()) // if m_destroy == true
		{
			delete s_vpGameObjectList[i];
			s_vpGameObjectList.erase(find(s_vpGameObjectList.begin(), s_vpGameObjectList.end(), s_vpGameObjectList[i]));
			i--; // as we delete the vector array will move all elements backwards so we need to move i back by one
		}
	}
}

void GameObjectManager::UpdateAllDestroyed()
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++) // loop through each object in the list
	{
		if (s_vpGameObjectList[i]->GetObjectType() == TYPE_DESTROYED)
		{
			s_vpGameObjectList[i]->SetAnimationSpeed(0.2f);
			s_vpGameObjectList[i]->UpdateMovement();
			s_vpGameObjectList[i]->UpdateAnimation();

			int frame = s_vpGameObjectList[i]->GetFrame();
			if (frame % 2)
			{
				s_vpGameObjectList[i]->SetRender(true);
			}
			else
			{
				s_vpGameObjectList[i]->SetRender(false);
			}

			if (s_vpGameObjectList[i]->IsOffDisplay() || frame >= 10)
				s_vpGameObjectList[i]->Destroy();
		}
	}
}

int GameObjectManager::GetAllObjectsOfType(GameObjectType objType, std::vector<GameObjectClass*>& objList)
{
	objList.clear();

	int count = 0;
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->GetObjectType() == objType)
		{
			objList.push_back(s_vpGameObjectList[i]);
			count++;
		}
	}

	return count;
}

int GameObjectManager::GetAllObjectsOfType(GameObjectType objType, std::vector<GameObjectClass*>& objList, bool clearList)
{
	if (clearList == true)
		objList.clear();

	int count = 0;
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->GetObjectType() == objType)
		{
			objList.push_back(s_vpGameObjectList[i]);
			count++;
		}
	}

	return count;
}

void GameObjectManager::RemoveTools() // used on respawning
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->GetObjectType() == TYPE_TOOL)
			s_vpGameObjectList[i]->Destroy();
	}
}

void GameObjectManager::DeleteGameObjectsByType(GameObjectType type)
{
	for (int i = 0; i < s_vpGameObjectList.size(); i++)
	{
		if (s_vpGameObjectList[i]->GetObjectType() == type)
			s_vpGameObjectList[i]->Destroy(); // <-- remember this funtion does not immediatly destroy the objects but sets them to be deleted later
	}
}