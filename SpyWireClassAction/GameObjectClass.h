#pragma once
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
	GameObjectClass(); // default constructor - when you make a GameObject with no parameters
	GameObjectClass( GameObjectType objType, Point2f position, Vector2f velocity, std::string spriteName);
	virtual ~GameObjectClass() {};

	virtual void Update() {};
	virtual void OnCollision() {};
	
	bool CheckDestroy() { return m_destroy; };
	bool CollisionTest(GameObjectClass* objA, GameObjectClass* objB);
	bool IsLeavingDisplay();
	bool IsLeavingDisplay(bool vertical, bool horizontal);
	bool IsOffDisplay();
	bool GetRender() { return m_render; };
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
	int GetSpriteID() { return m_spriteID; };

	GameObjectType GetObjectType() { return m_type; };
protected:

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
};

