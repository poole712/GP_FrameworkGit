#ifndef _ENTITY_H
#define _ENTITY_H

#include "entity.h"
#include "vector2.h"
#include "elementtype.h"
#include "box2d/box2d.h"

class Renderer;
class Sprite;
class InputSystem;
class b2World;
class b2Vec2;
class Level;
class SoundSystem;

enum EntityType {
	Tile,
	Block,
	Player,
};

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual bool Initialise(Renderer& renderer, b2World& world) = 0;
	virtual bool Initialise(Renderer& renderer, b2World& world, Level& scene) = 0;
	virtual void Process(float deltaTime, InputSystem& inputSystem) = 0;
	virtual void Process(float deltaTime, InputSystem& inputSystem, SoundSystem& soundSystem, Level& scene) = 0;
	virtual void Draw(Renderer& renderer);

	void Rotate(float direction);
	void SetPosition(float posX, float posY);

	bool IsAlive() const;
	void SetAliveState(bool state);
	float GetRadius();
	float GetRotation();

	Vector2 GetFacingDirection();

	Vector2& GetPosition();
	Vector2& GetVelocity();

	bool IsCollidingWith(Entity& toCheck);
	EntityType GetEntityType();
	virtual void Toggle(ElementType type) = 0;

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

public:

protected:
	Sprite* m_pSprite;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_rotation;
	b2Vec2 m_vStartPos;
	bool m_bAlive;
	float m_fCurrentRotation;
	EntityType m_entityType;


private:

};

#endif // !_ENTITY_H
