#include "entity.h"

#include "renderer.h"
#include <cmath>
#include <string>    
#include "sprite.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"
#include "logmanager.h"


#include <cassert>
#include <cstdlib>

Entity::Entity()
	: m_pSprite(0), m_bAlive(true), m_bUpdateWithVel(true), m_bToggledOn(false)
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

void
Entity::SetElementType(ElementType type)
{
	m_elementType = type;
}

bool
Entity::Initialise(Renderer& renderer, b2World& world)
{
	return true;
}

void
Entity::Process(float deltaTime, InputSystem& inputSystem)
{
	if (m_bUpdateWithVel)
	{
		m_position += m_velocity * deltaTime;
	}
	m_pSprite->Process(deltaTime);
}


void
Entity::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pSprite->Draw(renderer);
	}
}

Vector2&
Entity::GetPosition()
{
	return m_position;
}

Vector2&
Entity::GetVelocity()
{
	return m_velocity;
}

void 
Entity::Rotate(float direction)
{
	m_fCurrentRotation = direction;

	m_pSprite->SetAngle(direction);
}

bool 
Entity::IsAlive() const
{
	return m_bAlive;
}

void
Entity::SetAliveState(bool state)
{
	m_bAlive = state;
}

float
Entity::GetRadius()
{
	return m_pSprite->GetScale();
}

Vector2
Entity::GetFacingDirection()
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
Entity::IsCollidingWith(Entity& toCheck)
{
	if (m_bAlive)
	{
		// Corrected distance calculation
		float dx = toCheck.m_position.x - m_position.x;
		float dy = toCheck.m_position.y - m_position.y;

		// Calculate the squared distance
		float distanceSquared = dx * dx + dy * dy;

		// Calculate the actual distance
		float distance = std::sqrt(distanceSquared);

		// Log the distance
		std::string logMessage = "Distance between entities: " + std::to_string(distance);
		LogManager::GetInstance().Log(logMessage.c_str());


		// Calculate the squared sum of radii
		float radiiSum = 100;
		float radiiSumSquared = radiiSum * radiiSum;
		// Return if the squared distance is less than or equal to the squared sum of radii
		return distanceSquared <= radiiSumSquared;
	}
	return false;
}

void
Entity::SetPosition(float posX, float posY)
{
	m_position.x = posX;
	m_position.y = posY;
	m_pSprite->SetX(static_cast<int>(posX));
	m_pSprite->SetY(static_cast<int>(posY));
}

float
Entity::GetRotation()
{
	return m_fCurrentRotation;
}

ElementType 
Entity::GetElementType() 
{
	return m_elementType;
}

bool
Entity::IsToggledOn()
{
	return m_bToggledOn;
}