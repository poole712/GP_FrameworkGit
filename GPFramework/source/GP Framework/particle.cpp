#include "particle.h"

#include "renderer.h"
#include "sprite.h"

Particle::Particle()
	: m_bAlive(false), m_fCurrentAge(0.0f)
{

}

Particle::~Particle()
{

}

bool
Particle::Initialise(Sprite& sprite)
{
	m_pSharedSprite = &sprite;
	return true;
}

void 
Particle::Process(float deltaTime)
{
	if (m_bAlive)
	{
		m_fCurrentAge += deltaTime;
		m_acceleration.x -= m_fCurrentAge * 5;
		m_acceleration.y -= m_fCurrentAge * 5;

		m_velocity += m_acceleration * deltaTime;
		m_position += m_velocity * deltaTime;

		if (m_fCurrentAge > m_fMaxLifespan)
		{
			m_bAlive = false;
		}
	}
}

void 
Particle::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pSharedSprite->SetRedTint(m_fColour[0]);
		m_pSharedSprite->SetGreenTint(m_fColour[1]);
		m_pSharedSprite->SetBlueTint(m_fColour[2]);
		float alpha = 1.0f - (m_fCurrentAge / m_fMaxLifespan);
		m_pSharedSprite->SetAlpha(alpha);
		m_pSharedSprite->SetX(m_position.x);
		m_pSharedSprite->SetY(m_position.y);
		m_pSharedSprite->Draw(renderer);
	}
}