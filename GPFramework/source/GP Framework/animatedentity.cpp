#include "animatedentity.h"

#include "renderer.h"
#include "animatedsprite.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"
#include "logmanager.h"
#include "entity.h"

#include <cassert>
#include <cstdlib>

AnimatedEntity::AnimatedEntity()
	: m_pASprite(nullptr), m_bAlive(true)
{

}

AnimatedEntity::~AnimatedEntity()
{
	delete m_pASprite;
	m_pASprite = 0;
}

Vector2&
AnimatedEntity::GetPosition()
{
	return m_position;
}

Vector2&
AnimatedEntity::GetVelocity()
{
	return m_velocity;
}

void
AnimatedEntity::Rotate(float direction)
{
	m_fCurrentRotation = direction;

	m_pASprite->SetAngle(direction);
}

bool
AnimatedEntity::IsAlive() const
{
	return m_bAlive;
}

void
AnimatedEntity::SetAliveState(bool state)
{
	m_bAlive = state;
}

float
AnimatedEntity::GetRadius()
{
	return m_pASprite->GetScale();
}

Vector2
AnimatedEntity::GetFacingDirection()
{
	if (m_velocity.LengthSquared() > 0.0f)
	{
		m_velocity.Normalise();
		return m_velocity;
	}
	else
	{
		return Vector2(1.0f, 0.0f);
	}
}

bool
AnimatedEntity::IsCollidingWith(Entity& toCheck)
{
	if (m_bAlive)
	{
		// Corrected distance calculation
		float dx = toCheck.GetPosition().x - m_position.x;
		float dy = toCheck.GetPosition().y - m_position.y;

		// Calculate the squared distance
		float distanceSquared = dx * dx + dy * dy;

		// Calculate the squared sum of radii
		float radiiSum = 50 + 50;
		float radiiSumSquared = radiiSum * radiiSum;
		// Return if the squared distance is less than or equal to the squared sum of radii
		return distanceSquared <= radiiSumSquared;
	}
	return false;
}

void
AnimatedEntity::SetPosition(float posX, float posY)
{
	m_position.x = posX;
	m_position.y = posY;
	m_pASprite->SetX(static_cast<int>(posX));
	m_pASprite->SetY(static_cast<int>(posY));
}

float
AnimatedEntity::GetRotation()
{
	return m_fCurrentRotation;
}

