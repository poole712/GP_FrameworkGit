#include "laserbullet.h"

#include "logmanager.h"
#include "renderer.h"
#include "lasercannon.h"
#include "sprite.h"



LaserBullet::LaserBullet()

{
	LogManager::GetInstance().Log("Laser bullet constructed");
}

LaserBullet::~LaserBullet()
{

}


bool
LaserBullet::Initialise(Renderer& renderer)
{

	m_pSprite = renderer.CreateSprite("sprites\\ball.png");
	m_pSprite->SetScale(0.025f);
	m_pSprite->SetBlueTint(0.0f);
	m_pSprite->SetRedTint(0.0f);

	return true;
}

void
LaserBullet::Setup(LaserCannon& player)
{
	m_position.x = player.GetPosition().x;
	m_position.y = player.GetPosition().y - 50;
	SetAliveState(true);
	m_velocity.y = -50.0f;
	m_velocity.x = 0.0f;
}

void
LaserBullet::Process(float deltaTime, InputSystem& inputSystem)
{
	m_position += m_velocity * deltaTime;
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));

}

void
LaserBullet::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pSprite->Draw(renderer);

	}
}
