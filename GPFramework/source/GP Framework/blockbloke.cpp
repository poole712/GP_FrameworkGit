#include "blockbloke.h"

#include "logmanager.h"
#include "renderer.h"
#include "sprite.h"
#include "soundsystem.h"
#include "shield.h"
#include "inputsystem.h"
#include "box2d/box2d.h"

#include <SDL_scancode.h>


#include <thread>
#include <chrono>


float BlockBloke::sm_fBoundaryWidth = 0.0f;
float BlockBloke::sm_fBoundaryHeight = 0.0f;

BlockBloke::BlockBloke()
	: m_pShield(0), m_iAmmo(0), m_bCanFire(false), m_fFireCooldown(0), m_fTimeSinceLastFire(0), m_iHealth(5)
{
}

BlockBloke::~BlockBloke()
{
	delete m_pShield;
	m_pShield = 0;

}

bool
BlockBloke::Initialise(Renderer& renderer)
{
	return true;
}

bool
BlockBloke::Initialise(Renderer& renderer, b2World* world)
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

	m_pShield = new Shield();
	m_pShield->Initialise(renderer, world);
	m_pShield->SetPosition(m_position.x, m_position.y - 25.0f);

	return true;
}

void
BlockBloke::Process(float deltaTime, InputSystem& inputSystem)
{
	m_position += m_velocity * deltaTime;
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));
	
	//shield->Process(deltaTime);
	m_pSprite->Process(deltaTime);
	m_pShield->Process(deltaTime, inputSystem);

	m_fTimeSinceLastFire += deltaTime;

	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));
	ButtonState leftArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_LEFT));
	ButtonState rightArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_RIGHT));

	if (leftArrowState == BS_HELD && rightArrowState == BS_NEAUTRAL)
	{
		m_pShield->ShieldRotate(15);
	}
	if (rightArrowState == BS_HELD && leftArrowState == BS_NEAUTRAL)
	{
		m_pShield->ShieldRotate(-15);
	}

	if (m_fTimeSinceLastFire >= m_fFireCooldown)
	{
		m_bCanFire = true; // Allow firing again after cooldown
	}
}

void
BlockBloke::Draw(Renderer& renderer)
{
	m_pSprite->Draw(renderer);
	m_pShield->Draw(renderer);

}



void
BlockBloke::ShootBullet(SoundSystem& soundSystem)
{
	if (m_iAmmo > 0)
	{
		//shield->ShootBullet(soundSystem);
	}
}

void
BlockBloke::Move(float x)
{
	m_velocity.x = x;

}

void 
BlockBloke::FireDelay(int milliseconds)
{
	
}