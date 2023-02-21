#pragma once

enum Agent8State // <- copyed these here as there is no header to include for them - this will allow me to avoid #including the states in each other, as can be seen in SwitchStates(StateBaseClass* newState).
{
	STATE_APPEAR = 0,
	STATE_HALT,
	STATE_PLAY,
	STATE_DEAD,
};

enum GameObjectType // will need to copy this as there is not MainGame.h
{
	TYPE_NULL = -1,
	TYPE_AGENT8,
	TYPE_AGENT8_STATE,
	TYPE_FAN,
	TYPE_TOOL,
	TYPE_COIN,
	TYPE_STAR,
	TYPE_LASER,
	TYPE_DESTROYED,
};

class GameObjectClass
{
public:
	GameObjectClass() {}; // default constructor - when when you make a GameObject with no parameters
	GameObjectClass( GameObjectType objType, Point2f position, std::string spriteName);
	virtual ~GameObjectClass() {};

	static void UpdateAll();
	static void RenderAll();
	static void UpdateAllDestroyed();
	static void DeleteAll(); // used to delete all objs
	static void CleanUp(); // used to delete all objs marked for destruction at the end of each frame
	static GameObjectClass* GetPlayer() { return s_pPlayer; }; // used to delete all objs marked for destruction at the end of each frame
	static void SetPlayer(GameObjectClass* playerPointer) { s_pPlayer = playerPointer; }; // used to delete all objs marked for destruction at the end of each frame
	static void SetScorePointer(int* scorePointer) { s_pScore = scorePointer; }; // used to alter the score within the gameState without needing to include it within this file cauing a loop with Agent8

	virtual void Update() {};
	virtual void OnCollision() {};
	
	bool CheckDestroy() { return m_destroy; };
	bool CollisionTest(GameObjectClass* objA, GameObjectClass* objB);
	bool IsLeavingDisplay();
	bool IsLeavingDisplay(bool vertical, bool horizontal);
	bool IsOffDisplay();

	std::vector<GameObjectClass*> GetAllObjectsOfType(GameObjectType objType);

	void UpdateMovement();
	void UpdateAnimation();
	void Respawn();
	void Destroy();
	void SetVelocity(Vector2f velocity) { m_velocity = velocity; };
	void SetAcceleration(Vector2f acceleration) { m_acceleration = acceleration; };
	void SetPosition(Point2f pos) { m_position = pos; };
	void SetSpriteName(std::string spriteName, float animationSpeed);
	void SetAnimationSpeed(float animationSpeed) { m_animationSpeed = animationSpeed; };
	void SetRotation(float rotation) { m_rotation = rotation; };
	void SetRotationSpeed(float rotationSpeed) { m_rotationSpeed = rotationSpeed; };
	void SetFrame(float frame) { m_frame = frame; };
	void SetRender(bool render) { m_render = render; };

	Vector2f GetVelocity() { return m_velocity; };
	Vector2f GetAcceleration () { return m_acceleration; };
	Vector2f GetPosition() { return m_position; };
	float GetRotation() { return m_rotation; };
	float GetFrame() { return m_frame; };
	float GetSpriteID() { return m_spriteID; };
	bool GetRender() { return m_render; };

	GameObjectType GetObjectType() { return m_type; };
protected:
	static GameObjectClass* s_pPlayer; // static player pointer as there can only be one, that will be share by all (new and old) game objects
	static int* s_pScore;

	bool m_destroy{ false }; // used to tell when to switch states / destroy this state (can't even not have a state) - must be deleted at end of frame
	bool m_render{ true };

	std::string m_spriteName{ "" };
	int m_spriteID{ -1 };
	int m_spriteWidth{ -1 };
	int m_spriteHeight{ -1 };
	float m_frame{ -1 };
	float m_frameTimer{ 0 };
	float m_rotation{ 0 };
	float m_rotationSpeed{ 0 };
	float m_animationSpeed{ 1 }; // animations can have a default speed of 1
	float m_radius{ -1 };

	Point2f m_position{ 0, 0 };
	Point2f m_oldPosition{ 0, 0 };
	Vector2f m_velocity{ 0, 0 };
	Vector2f m_acceleration{ 0, 0 };

	GameObjectType m_type{ GameObjectType::TYPE_NULL };

private:
	static std::vector<GameObjectClass*> s_vpGameObjectList;
};

