#ifndef _ANIMATEDENTITY_H
#define _ANIMATEDENTITY_H

#include "animatedentity.h"
#include "vector2.h"

class Renderer;
class AnimatedSprite;
class InputSystem;
class Entity;

class AnimatedEntity
{
public:
	AnimatedEntity();
	virtual ~AnimatedEntity();

	virtual bool Initialise(Renderer& renderer) = 0;
	virtual void Process(float deltaTime) = 0;
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

protected:

private:
	AnimatedEntity(const AnimatedEntity& entity);
	AnimatedEntity& operator=(const AnimatedEntity& entity);

public:

protected:
	AnimatedSprite* m_pASprite;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_rotation;
	bool m_bAlive;
	float m_fCurrentRotation;


private:

};

#endif // !_ENTITY_H
