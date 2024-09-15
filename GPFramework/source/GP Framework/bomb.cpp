#include "bomb.h"

#include "renderer.h"
#include "animatedentity.h"
#include "animatedsprite.h"

Bomb::Bomb()
{

}

Bomb::~Bomb()
{
	AnimatedEntity::~AnimatedEntity();
}

bool
Bomb::Initialise(Renderer& renderer)
{
	m_pASprite = renderer.CreateAnimatedSprite("sprites\\Bomb.png");
	m_pASprite->SetupFrames(128, 128);
	m_pASprite->SetLooping(true);
	m_pASprite->SetFrameDuration(0.25f);
	m_pASprite->SetScale(1.0f);

	SetPosition(640, 0);

	m_velocity.y = 150.0f;

	return true;
}


void
Bomb::Process(float deltaTime)
{
	if (m_bAlive)
	{
		AnimatedEntity::Process(deltaTime);
		if (m_position.y > 720 || m_position.y < 0)
		{
			Rotate(0);
			SetPosition(640, 0);
			SetAliveState(false);
			m_velocity.y = 150.0f;
		}
	}
	if (m_bHitPlayer)
	{
		SetPosition(640, 0);
		SetAliveState(false);
		Rotate(0);
		SetHitPlayer();
		m_velocity.y = 150.0f;
	}

}

void
Bomb::SetHitPlayer()
{
	m_bHitPlayer = !m_bHitPlayer;
}

void
Bomb::Deflect()
{
	m_position.y = m_position.y - 10.0f;
	m_velocity.y = -m_velocity.y;
	Rotate(180.0);
}

void
Bomb::Draw(Renderer& renderer)
{
	AnimatedEntity::Draw(renderer);
}
