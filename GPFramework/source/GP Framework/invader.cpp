#include "invader.h"

#include "logmanager.h"
#include "renderer.h"
#include "lasercannon.h"
#include "sprite.h"



Invader::Invader()
{
	LogManager::GetInstance().Log("Invader constructed");
}

Invader::~Invader()
{

}


bool
Invader::Initialise(Renderer& renderer)
{
	m_velocity.y = 3.0f;

	m_pSprite = renderer.CreateSprite("sprites\\triangle.png");
	m_pSprite->SetScale(0.05f);
	m_pSprite->SetBlueTint(0.0f);
	m_pSprite->SetGreenTint(0.0f);

	return true;
}


void
Invader::Process(float deltaTime, InputSystem& inputSystem)
{
	m_position += m_velocity * deltaTime;
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));

	if (IsCollidingWith(*m_pPlayer))
	{
		LogManager::GetInstance().Log("Player dead");
	}

}

void
Invader::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pSprite->Draw(renderer);

	}
}

void
Invader::SetPlayerRef(LaserCannon& lasercannon)
{
	m_pPlayer = &lasercannon;
}

void 
Invader::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}