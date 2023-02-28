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
	static GameObjectClass* GetPlayer(int index) { return s_pPlayerList[index]; };
	static int GetTotalPlayer() { return s_pPlayerList.size(); }; // Will return the number of players - useful for when needing to loop through each player
	static int GetAllPlayer(std::vector<GameObjectClass*>& list); // Will alter the list given as a parameter to contain all the players.
	static int GetAllPlayer(std::vector<GameObjectClass*>& list, bool clearList); // If you don't clear the list the function will check that each player is not in the list.
	static void AddPlayer(GameObjectClass* playerPointer) { s_pPlayerList.push_back(playerPointer); }; // used to delete all objs marked for destruction at the end of each frame
	static void RemoveTools();

	static int GetAllObjectsOfType(GameObjectType objType, std::vector<GameObjectClass*>& objList); // int is the number objects added to the list.
	static int GetAllObjectsOfType(GameObjectType objType, std::vector<GameObjectClass*>& objList, bool clearList); // int is the number objects added to the list - clear list will clear the list before adding (is on by default).


	static void RegisterGameObject(GameObjectClass* obj) { s_vpGameObjectList.push_back(obj); };
	static void DeleteGameObjectsByType(GameObjectType type);
protected:
private:
	static std::vector<GameObjectClass*> s_vpGameObjectList; // Must never be used outside of the GameObject Manager for code safety reasons - mainly stuff being deleted

	static std::vector<GameObjectClass*> s_pPlayerList; // static player pointer as there can only be one, that will be share by all (new and old) game objects
};

