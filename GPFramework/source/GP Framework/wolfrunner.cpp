#include "wolfrunner.h"

#include "logmanager.h"
#include "renderer.h"
#include "animatedsprite.h"


WolfRunner::WolfRunner(bool goingLeft)
	:m_bGoingLeft(goingLeft)
{

}

WolfRunner::~WolfRunner()
{
	Enemy::~Enemy();
}


bool
WolfRunner::Initialise(Renderer& renderer)
{

	if (!m_bGoingLeft)
	{
		m_pASprite = renderer.CreateAnimatedSprite("sprites\\WolfRunnerGoingLeft.png");
		SetPosition(1280, 600);
		m_vResetPos.x = 1280;
		m_vResetPos.y = 600;
		m_velocity.x = -150.0f;

	}
	else {
		m_pASprite = renderer.CreateAnimatedSprite("sprites\\WolfRunnerGoingRight.png");
		SetPosition(0, 600);
		m_vResetPos.x = 0;
		m_vResetPos.y = 600;
		m_velocity.x = 150.0f;

	}

	m_pASprite->SetupFrames(128, 128);
	m_pASprite->SetLooping(true);
	m_pASprite->SetFrameDuration(0.25f);

	return true;
}


void
WolfRunner::Process(float deltaTime)
{
	if (m_bAlive)
	{
		AnimatedEntity::Process(deltaTime);
	
		if (m_position.x > 1280 || m_position.y < 0)
		{
			SetPosition(m_vResetPos.x, m_vResetPos.y);
			SetAliveState(false);
		}
	}

}

void
WolfRunner::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pASprite->Draw(renderer);

	}
}

void
WolfRunner::Die()
{
}

void
WolfRunner::SetPositionWithResetPos(float x, float y)
{
	m_vResetPos.x = x;
	m_vResetPos.y = y;
	SetPosition(x, y);
	SetAliveState(true);
}
