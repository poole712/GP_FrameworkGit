#pragma once
#ifndef _ANIMATEDENTITY_H
#define _ANIMATEDENTITY_H

#include "animatedentity.h"
#include "vector2.h"
#include "entity.h"

class Renderer;
class AnimatedSprite;
class InputSystem;
class Entity;

class AnimatedEntity : public Entity
{
public:
	AnimatedEntity();
	virtual ~AnimatedEntity();

	bool Initialise(Renderer& renderer, b2World& world) { return true; };
	void Process(float deltaTime, InputSystem& inputSystem) {};
	void Draw(Renderer& renderer) {};
	bool IsAnimationCollidingWith(Entity& toCheck);
	Vector2 GetAnimatedPos();
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

	InputSystem* m_iInputSystem;

private:

};

#endif // !_ANIMATED_ENTITY_H