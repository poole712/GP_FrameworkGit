#include "animatedentity.h"

#include "renderer.h"
#include "animatedsprite.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"
#include "logmanager.h"
#include "entity.h"
#include "box2d/box2d.h"
#include "inlinehelper.h"

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <string>    

AnimatedEntity::AnimatedEntity()
	: m_pASprite(nullptr), m_bAlive(true)
{
	m_bUpdateWithVel = false;
}

AnimatedEntity::~AnimatedEntity()
{
	delete m_pASprite;
	m_pASprite = 0;

	delete m_iInputSystem;
	m_iInputSystem = 0;
}

bool
AnimatedEntity::IsAnimationCollidingWith(Entity& toCheck)
{
	if (m_bAlive)
	{
		// Corrected distance calculation
		float dx = toCheck.GetPosition().x - m_position.x;
		float dy = toCheck.GetPosition().y - m_position.y;

		// Calculate the squared distance
		float distanceSquared = dx * dx + dy * dy;

		// Calculate the actual distance
		float distance = std::sqrt(distanceSquared);



		// Calculate the squared sum of radii
		float radiiSum = 100;
		float radiiSumSquared = radiiSum * radiiSum;
		// Return if the squared distance is less than or equal to the squared sum of radii
		return distanceSquared <= radiiSumSquared;
	}
	return false;
}

Vector2
AnimatedEntity::GetAnimatedPos()
{
	m_position.x = m_pASprite->GetX();
	m_position.y = m_pASprite->GetY();

	return m_position;
}
