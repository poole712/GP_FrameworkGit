#include "fireball.h"

#include "renderer.h"
#include "animatedentity.h"
#include "animatedsprite.h"
#include "explosion.h"

Fireball::Fireball(bool goingLeft)
	: m_bGoingRight(goingLeft)
{

}

Fireball::~Fireball()
{
	AnimatedEntity::~AnimatedEntity();
}

bool
Fireball::Initialise(Renderer& renderer)
{
	m_pASprite = renderer.CreateAnimatedSprite("sprites\\Fireball.png");
	m_pASprite->SetupFrames(128, 128);
	m_pASprite->SetLooping(true);
	m_pASprite->SetFrameDuration(0.5f);
	m_pASprite->SetScale(0.5f);
	
	if (m_bGoingRight)
	{
		m_velocity.x = 250.0f;
	}
	else 
	{
		//Rotate(180.0f);
		m_velocity.x = -250.0f;
	}

	m_bFlying = true;

	return true;
}


void
Fireball::Process(float deltaTime)
{
	if (m_bAlive)
	{
		AnimatedEntity::Process(deltaTime);
		if (m_position.x > 1280 || m_position.x < 0)
		{
			SetPosition(m_vFireballPos.x, m_vFireballPos.y);
			SetAliveState(false);
		}
	}

}

void
Fireball::Deflect()
{
	m_velocity.x = m_velocity.x * -1;
	Rotate(180.0);
}

void
Fireball::Draw(Renderer& renderer)
{
	AnimatedEntity::Draw(renderer);
}

void
Fireball::SetPositionWithResetPos(float x, float y)
{
	m_vFireballPos.x = x; 
	m_vFireballPos.y = y;
	SetPosition(x, y);
	SetAliveState(true);
}
