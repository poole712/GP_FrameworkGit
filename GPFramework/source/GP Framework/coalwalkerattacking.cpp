#include "coalwalkerattacking.h"

#include "logmanager.h"
#include "renderer.h"
#include "animatedsprite.h"


CoalWalkerAttacking::CoalWalkerAttacking(bool goingLeft)
	:m_bGoingLeft(goingLeft)
{

}

CoalWalkerAttacking::~CoalWalkerAttacking()
{
	Enemy::~Enemy();
}


bool
CoalWalkerAttacking::Initialise(Renderer& renderer)
{

	if (!m_bGoingLeft)
	{
		m_pASprite = renderer.CreateAnimatedSprite("sprites\\CoalWalkerShootingLeft.png");
		SetPosition(1280, 600);
	}
	else {
		m_pASprite = renderer.CreateAnimatedSprite("sprites\\CoalWalkerShootingRight.png");
		SetPosition(0, 600);
	}

	m_pASprite->SetupFrames(128, 128);
	m_pASprite->SetLooping(true);
	m_pASprite->SetFrameDuration(1.0f);

	return true;
}

void
CoalWalkerAttacking::Shoot()
{
	LogManager::GetInstance().Log("Shooting from Coal Walker");
}

void
CoalWalkerAttacking::Process(float deltaTime)
{
	m_position += m_velocity * deltaTime;
	m_pASprite->SetX(static_cast<int>(m_position.x));
	m_pASprite->SetY(static_cast<int>(m_position.y));
	m_pASprite->Process(deltaTime);
	m_pASprite->Animate();


}

void
CoalWalkerAttacking::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pASprite->Draw(renderer);

	}
}

void
CoalWalkerAttacking::Die()
{
}
