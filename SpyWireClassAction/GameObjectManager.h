#pragma once

class GameObjectClass;

class GameObjectManager
{
public:
	static GameObjectClass* CreateObject(GameObjectType objType, Point2f pos, Vector2f vel);

	static void UpdateAll();
	static void RenderAll();
	static void UpdateAllDestroyed();
	static void DeleteAll(); // used to delete all objs
	static void CleanUp(); // used to delete all objs marked for destruction at the end of each frame
	static GameObjectClass* GetPlayer() { return s_pPlayer; }; // used to delete all objs marked for destruction at the end of each frame
	static void SetPlayer(GameObjectClass* playerPointer) { s_pPlayer = playerPointer; }; // used to delete all objs marked for destruction at the end of each frame
	static void SetScorePointer(int* scorePointer) { s_pScore = scorePointer; }; // used to alter the score within the gameState without needing to include it within this file cauing a loop with Agent8
	static void RemoveTools();

	static int* GetScorePointer() { return s_pScore; };

	static int GetAllObjectsOfType(GameObjectType objType, std::vector<GameObjectClass*>& objList); // int is the number objects added to the list.
	static int GetAllObjectsOfType(GameObjectType objType, std::vector<GameObjectClass*>& objList, bool clearList); // int is the number objects added to the list - clear list will clear the list before adding (is on by default).


	static void RegisterGameObject(GameObjectClass* obj) { s_vpGameObjectList.push_back(obj); };
	static void DeleteGameObjectsByType(GameObjectType type);
protected:
private:
	static std::vector<GameObjectClass*> s_vpGameObjectList; // Must never be used outside of the GameObject Manager for code safety reasons - mainly stuff being deleted

	static GameObjectClass* s_pPlayer; // static player pointer as there can only be one, that will be share by all (new and old) game objects
	static int* s_pScore;

};

