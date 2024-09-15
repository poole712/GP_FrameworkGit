#include "coalwalkermoving.h"

#include "logmanager.h"
#include "renderer.h"
#include "animatedsprite.h"


CoalWalkerMoving::CoalWalkerMoving(bool goingLeft)
	:m_bGoingLeft(goingLeft)
{

}

CoalWalkerMoving::~CoalWalkerMoving()
{
	Enemy::~Enemy();
}


bool
CoalWalkerMoving::Initialise(Renderer& renderer)
{

	if (!m_bGoingLeft)
	{
		m_pASprite = renderer.CreateAnimatedSprite("sprites\\CoalWalkerGoingLeft.png");
		SetPosition(1290, 600);
		m_velocity.x = -25.0;

	}
	else {
		m_pASprite = renderer.CreateAnimatedSprite("sprites\\CoalWalkerGoingRight.png");
		SetPosition(-10, 600);
		m_velocity.x = 25.0f;
	}

	m_pASprite->SetupFrames(128, 128);
	m_pASprite->SetLooping(true);
	m_pASprite->SetFrameDuration(0.5f);

	return true;
}

void 
CoalWalkerMoving::ResetPosition()
{
	if (!m_bGoingLeft)
	{
		SetPosition(1280, 600);
		m_velocity.x = -15.0f;

	}
	else {
		SetPosition(0, 600);
		m_velocity.x = 15.0f;
	}
}

void
CoalWalkerMoving::Process(float deltaTime)
{
	m_position += m_velocity * deltaTime;
	m_pASprite->SetX(static_cast<int>(m_position.x));
	m_pASprite->SetY(static_cast<int>(m_position.y));
	m_pASprite->Process(deltaTime);
	m_pASprite->Animate();


}

void
CoalWalkerMoving::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pASprite->Draw(renderer);

	}
}

void 
CoalWalkerMoving::Die()
{
}
