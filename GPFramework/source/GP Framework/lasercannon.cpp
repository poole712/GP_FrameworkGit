#include "lasercannon.h"

#include "logmanager.h"
#include "renderer.h"
#include "laserbullet.h"
#include "sprite.h"
#include "soundsystem.h"

#include <thread>
#include <chrono>

float LaserCannon::sm_fBoundaryWidth = 0.0f;
float LaserCannon::sm_fBoundaryHeight = 0.0f;

LaserCannon::LaserCannon()
	: m_pBullets(0), m_bCanFire(true), m_fTimeSinceLastFire(0.0f), m_fFireCooldown(1.0f), m_iBulletIndex(0)
{
	LogManager::GetInstance().Log("Laser Cannon constructed");
}

LaserCannon::~LaserCannon()
{

}

bool
LaserCannon::Initialise(Renderer& renderer)
{
	m_pSprite = renderer.CreateSprite("sprites\\triangle.png");
	m_pSprite->SetScale(0.1f);
	Rotate(180.0f);
	m_pSprite->SetBlueTint(0.0f);
	m_pSprite->SetRedTint(0.0f);

	const int EDGE_LIMIT = m_pSprite->GetWidth();
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	sm_fBoundaryWidth = static_cast<float>(SCREEN_WIDTH);
	sm_fBoundaryHeight = static_cast<float>(SCREEN_HEIGHT);

	m_position.x = SCREEN_WIDTH / 2.0f;
	m_position.y = (SCREEN_HEIGHT / 1.25f);

	for (int i = 0; i < 100; ++i) {
		m_pBullets.push_back(new LaserBullet());
	}
	for (LaserBullet* bullet : m_pBullets)
	{
		bullet->Initialise(renderer);
	}

	return true;
}

void
LaserCannon::Process(float deltaTime, InputSystem& inputSystem)
{
	m_position += m_velocity * deltaTime;
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));
	for (LaserBullet* bullet : m_pBullets)
	{
		bullet->Process(deltaTime, inputSystem);
	}

	m_fTimeSinceLastFire += deltaTime;

	if (m_fTimeSinceLastFire >= m_fFireCooldown)
	{
		m_bCanFire = true; // Allow firing again after cooldown
	}
}

void 
LaserCannon::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pSprite->Draw(renderer);
		for (LaserBullet* bullet : m_pBullets)
		{
			bullet->Draw(renderer);
		}
	}
}

void
LaserCannon::ShootBullet(SoundSystem &soundSystem)
{
	if (m_pBullets.size() > 0 && m_bCanFire)
	{
		soundSystem.PlaySound("Land");
		m_pBullets[m_iBulletIndex++]->Setup(*this);
		m_bCanFire = false;
		m_fTimeSinceLastFire = 0.0f;
	}
}

void
LaserCannon::Move(float x)
{
	m_velocity.x = x;

}


LaserBullet*
LaserCannon::GetCurrentBullet()
{
	if (m_iBulletIndex > 0)
	{
		return m_pBullets[m_iBulletIndex - 1];
	}
	else
	{
		return m_pBullets[0];

	}
}