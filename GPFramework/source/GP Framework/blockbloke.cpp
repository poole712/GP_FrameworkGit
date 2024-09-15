#define _CRT_SECURE_NO_WARNINGS


#include "blockbloke.h"

#include "logmanager.h"
#include "renderer.h"
#include "sprite.h"
#include "soundsystem.h"
#include "shield.h"
#include "inputsystem.h"
#include "box2d/box2d.h"
#include "explosion.h"

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

	delete m_pLeftR1;
	m_pLeftR1 = 0;
	delete m_pLeftR2;
	m_pLeftR2 = 0;
	delete m_pRightR1;
	m_pRightR1 = 0;
	delete m_pRightR2;
	m_pRightR2 = 0;

	delete m_pLeftExplosion;
	m_pLeftExplosion = 0;
	delete m_pRightExplosion;
	m_pRightExplosion = 0;
	delete m_pTopExplosion;
	m_pTopExplosion = 0;
}

bool
BlockBloke::Initialise(Renderer& renderer)
{
	return true;
}

bool
BlockBloke::Initialise(Renderer& renderer, b2World* world)
{
	m_fRotationSpeed = 10.0f;
	m_fHurtCooldown = 0.5f;
	m_fRotSfxCooldown = 0.1f;

	m_fJumpStrength = -600.0f;

	//Setting up sprites
	m_pSprite = renderer.CreateSprite("sprites\\UprightBB.png");
	m_pSprite->SetScale(1.25f);

	m_pLeftR1 = renderer.CreateSprite("sprites\\RotateLeftBB1.png");
	m_pLeftR1->SetScale(1.25f);
	m_pLeftR1->SetAngle(180.0f);

	m_pLeftR2 = renderer.CreateSprite("sprites\\RotateLeftBB2.png");
	m_pLeftR2->SetScale(1.25f);
	m_pLeftR2->SetAngle(180.0f);

	m_pRightR1 = renderer.CreateSprite("sprites\\RotateRightBB1.png");
	m_pRightR1->SetScale(1.25f);
	m_pRightR1->SetAngle(180.0f);

	m_pRightR2 = renderer.CreateSprite("sprites\\RotateRightBB2.png");
	m_pRightR2->SetScale(1.25f);
	m_pRightR2->SetAngle(180.0f);

	Rotate(180.0f);

	//Physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(640.0f, 600.0f);
	m_pBody = world->CreateBody(&bodyDef);
	m_pBody->SetGravityScale(2.5f);

	b2PolygonShape polyShape;
	polyShape.SetAsBox(1.0f, 1.0f);
	m_pShape = &polyShape;

	b2FixtureDef fixDef;
	fixDef.shape = &polyShape;
	fixDef.density = 0.5;
	fixDef.friction = 0.3f;

	m_pFixture = m_pBody->CreateFixture(&fixDef);

	m_pShield = new Shield();
	m_pShield->Initialise(renderer, world);
	m_pShield->SetPosition(m_position.x, m_position.y - 25.0f);

	m_pLeftExplosion = new Explosion();
	m_pLeftExplosion->Initialise(renderer);

	m_pRightExplosion = new Explosion();
	m_pRightExplosion->Initialise(renderer);

	m_pTopExplosion = new Explosion();
	m_pTopExplosion->Initialise(renderer);

	return true;
}

void
BlockBloke::Process(float deltaTime, InputSystem& inputSystem, SoundSystem& soundSystem)
{
	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);

	m_pLeftExplosion->SetThePosition(m_pBody->GetPosition().x - 50.0f, m_pBody->GetPosition().y);
	m_pRightExplosion->SetThePosition(m_pBody->GetPosition().x + 50.0f, m_pBody->GetPosition().y);
	m_pTopExplosion->SetThePosition(m_pBody->GetPosition().x, m_pBody->GetPosition().y - 60);

	m_pLeftR1->SetX(m_pBody->GetPosition().x);
	m_pLeftR1->SetY(m_pBody->GetPosition().y);

	m_pLeftR2->SetX(m_pBody->GetPosition().x);
	m_pLeftR2->SetY(m_pBody->GetPosition().y);

	m_pRightR1->SetX(m_pBody->GetPosition().x);
	m_pRightR1->SetY(m_pBody->GetPosition().y);

	m_pRightR2->SetX(m_pBody->GetPosition().x);
	m_pRightR2->SetY(m_pBody->GetPosition().y);

	//shield->Process(deltaTime);
	m_pSprite->Process(deltaTime);
	m_pShield->Process(deltaTime, inputSystem);
	m_pShield->SetPosition(m_pBody->GetPosition().x, m_pBody->GetPosition().y);

	m_position.x = m_pBody->GetPosition().x;
	m_position.y = m_pBody->GetPosition().y;

	m_fTimeSinceLastFire += deltaTime;
	m_fTimeSinceJumpStarted += deltaTime;
	m_fTimeSinceLastHurt += deltaTime;
	m_fTimeSinceRotSfxPlayed += deltaTime;

	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));
	ButtonState leftArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_LEFT));
	ButtonState rightArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_RIGHT));


	if (leftArrowState == BS_HELD && rightArrowState == BS_NEAUTRAL && m_pShield->GetShieldRot() < 240)
	{
		m_pShield->ShieldRotate(m_fRotationSpeed);
		if (m_bCanPlayRotSfx)
		{
			soundSystem.PlaySound("Rotate");
			m_bCanPlayRotSfx = false;
			m_fTimeSinceRotSfxPlayed = 0;
		}
	}
	if (rightArrowState == BS_HELD && leftArrowState == BS_NEAUTRAL && m_pShield->GetShieldRot() > 120)
	{
		m_pShield->ShieldRotate(-m_fRotationSpeed);
		if (m_bCanPlayRotSfx)
		{
			soundSystem.PlaySound("Rotate");
			m_bCanPlayRotSfx = false;
			m_fTimeSinceRotSfxPlayed = 0;
		}
	}
	if (spaceState == BS_PRESSED)
	{
		Jump(soundSystem);
	}
	if (m_fTimeSinceRotSfxPlayed >= m_fRotSfxCooldown)
	{
		m_bCanPlayRotSfx = true;
	}
	if (m_fTimeSinceLastFire >= m_fFireCooldown)
	{
		m_bCanFire = true; // Allow firing again after cooldown
	}
	if (m_fTimeSinceLastHurt >= m_fHurtCooldown && m_bHurt)
	{
		m_bHurt = false; // Allow firing again after cooldown
		m_pLeftExplosion->SetAlive(false);
		m_pRightExplosion->SetAlive(false);
		m_pTopExplosion->SetAlive(false);
		HurtVisuals(false);
		m_bHurt = false;
	}
	m_pLeftExplosion->Process(deltaTime);
	m_pRightExplosion->Process(deltaTime);
	m_pTopExplosion->Process(deltaTime);
}

void BlockBloke::Process(float deltaTime, InputSystem& inputSystem)
{
}

void 
BlockBloke::Hurt(bool fireball, bool fireballLeft, bool bomb, SoundSystem& soundSystem)
{
	m_bHurt = true;
	HurtVisuals(true);
	if (fireball)
	{
		if (fireballLeft)
		{
			soundSystem.PlaySound("Fireball1");
			m_pLeftExplosion->SetAlive(true);
		}
		else 
		{
			soundSystem.PlaySound("Fireball2");
			m_pRightExplosion->SetAlive(true);
		}
	}
	if (bomb)
	{
		soundSystem.PlaySound("Explosion");
		m_pTopExplosion->SetAlive(true);

	}
	soundSystem.PlaySound("Hurt");
	m_fTimeSinceLastHurt = 0;
}

void
BlockBloke::HurtVisuals(bool on)
{
	if (on)
	{
		m_pSprite->SetBlueTint(0);
		m_pSprite->SetGreenTint(0);
		m_pLeftR1->SetBlueTint(0);
		m_pLeftR1->SetGreenTint(0);
		m_pLeftR2->SetBlueTint(0);
		m_pLeftR2->SetGreenTint(0);
		m_pRightR1->SetBlueTint(0);
		m_pRightR1->SetGreenTint(0);
		m_pRightR1->SetBlueTint(0);
		m_pRightR2->SetGreenTint(0);
	}
	else {
		m_pSprite->SetBlueTint(1);
		m_pSprite->SetGreenTint(1);
		m_pLeftR1->SetBlueTint(1);
		m_pLeftR1->SetGreenTint(1);
		m_pLeftR2->SetBlueTint(1);
		m_pLeftR2->SetGreenTint(1);
		m_pRightR1->SetBlueTint(1);
		m_pRightR1->SetGreenTint(1);
		m_pRightR1->SetBlueTint(1);
		m_pRightR2->SetGreenTint(1);
	}

}

void
BlockBloke::Jump(SoundSystem& soundSystem)
{
	if (m_pBody->GetPosition().y <= 605 && m_pBody->GetPosition().y >= 595)
	{
		b2Vec2 jumpVec = b2Vec2(0, m_fJumpStrength);
		soundSystem.PlaySound("Jump");
		soundSystem.SetVolume("Jump", 0.5f);
		m_pBody->ApplyLinearImpulse(jumpVec, m_pBody->GetPosition(), true);
	}
}

float
BlockBloke::GetShieldAngle()
{
	return m_pShield->GetShieldRot();
}

void
BlockBloke::Draw(Renderer& renderer)
{
	float rot = m_pShield->GetShieldRot();

	m_pLeftExplosion->Draw(renderer);
	m_pRightExplosion->Draw(renderer);
	m_pTopExplosion->Draw(renderer);


	if (rot > 200 && rot < 240)
	{
		m_pRightR1->Draw(renderer);
	}
	else if (rot > 240 && rot < 360)
	{
		m_pRightR2->Draw(renderer);
	}
	else if (rot < 140 && rot > 100)
	{
		m_pLeftR1->Draw(renderer);
	}
	else if (rot < 100 && rot > 0)
	{
		m_pLeftR2->Draw(renderer);
	}
	else
	{
		m_pSprite->Draw(renderer);

	}
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