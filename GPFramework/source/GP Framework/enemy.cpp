#include "enemy.h"

#include "logmanager.h"
#include "renderer.h"
#include "animatedsprite.h"


Enemy::Enemy()
	:m_fFireCooldown(1), m_bIsFiring(false)
{

}

Enemy::~Enemy()
{
	AnimatedEntity::~AnimatedEntity();
}

bool
Enemy::Initialise(Renderer& renderer)
{
	return true;
}

void
Enemy::StartAttacking()
{

}

void
Enemy::Process(float deltaTime)
{
	m_position += m_velocity * deltaTime;
	m_pASprite->SetX(static_cast<int>(m_position.x));
	m_pASprite->SetY(static_cast<int>(m_position.y));
	m_pASprite->Process(deltaTime);
	m_pASprite->Animate();
}

void
Enemy::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pASprite->Draw(renderer);

	}
}

void Enemy::Attack()
{
}

void Enemy::Die()
{
}
