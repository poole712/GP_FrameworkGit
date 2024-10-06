#define _CRT_SECURE_NO_WARNINGS


#include "fletchersplayer.h"

#include "logmanager.h"
#include "renderer.h"
#include "sprite.h"
#include "soundsystem.h"
#include "inputsystem.h"
#include "inlinehelper.h"
#include "box2d/box2d.h"

#include <SDL_scancode.h>
#include <thread>
#include <chrono>


float FletchersPlayer::sm_fBoundaryWidth = 0.0f;
float FletchersPlayer::sm_fBoundaryHeight = 0.0f;

FletchersPlayer::FletchersPlayer()
	: m_fTimeSinceJumpStarted(0)
{
	m_vStartPos = b2Vec2(650.0f, 850.0f);
}

FletchersPlayer::FletchersPlayer(float x, float y)
	: m_fTimeSinceJumpStarted(0)
{
	m_vStartPos = b2Vec2(x, y);
}

FletchersPlayer::~FletchersPlayer()
{
	
}

bool
FletchersPlayer::Initialise(Renderer& renderer, b2World& world)
{
	m_bAlive = true;

	m_vJump = b2Vec2(0, -50000.0f);
	//Setting up sprites
	m_pSprite = renderer.CreateSprite("sprites\\FletchsTestPlayer.png");

	//Physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(m_vStartPos.x, m_vStartPos.y);
	m_pBody = world.CreateBody(&bodyDef);
	m_pBody->SetFixedRotation(true);

	b2PolygonShape polyShape;
	polyShape.SetAsBox(30.0f, 30.0f);
	m_pShape = &polyShape;

	b2FixtureDef fixDef;
	fixDef.shape = &polyShape;
	fixDef.density = 0.1;
	fixDef.friction = 0.0f;
	fixDef.restitution = 0.0f;

	m_pFixture = m_pBody->CreateFixture(&fixDef);
	m_entityType = Player;

	return true;
}

void
FletchersPlayer::Process(float deltaTime, InputSystem& inputSystem, SoundSystem& soundSystem)
{
	//m_pBody->ApplyForce(m_vVelocity, m_pBody->GetPosition(), true);
	m_pBody->SetTransform(b2Vec2(650.0f, m_pBody->GetPosition().y), m_pBody->GetAngle());

	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);

	m_position.x = m_pBody->GetPosition().x;
	m_position.y = m_pBody->GetPosition().y;

	m_pSprite->SetAngle(m_pBody->GetAngle());

	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));

	if (spaceState == BS_PRESSED)
	{
		Jump(soundSystem);
	}
}

void 
FletchersPlayer::Process(float deltaTime, InputSystem& inputSystem)
{
	//m_pBody->ApplyForce(m_vVelocity, m_pBody->GetPosition(), true);
	m_pBody->SetTransform(b2Vec2(650.0f, m_pBody->GetPosition().y), m_pBody->GetAngle());

	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);

	m_position.x = m_pBody->GetPosition().x;
	m_position.y = m_pBody->GetPosition().y;

	m_pSprite->SetAngle(m_pBody->GetAngle());

	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));

	if (spaceState == BS_PRESSED)
	{
		Jump();
	}
}

void
FletchersPlayer::Jump()
{
	if (m_pBody->GetPosition().y > m_vStartPos.y)
	{
		m_pBody->ApplyLinearImpulse(m_vJump, m_pBody->GetPosition(), true);
	}
}


void
FletchersPlayer::Jump(SoundSystem& soundSystem)
{
	if (m_pBody->GetPosition().y >= 900)
	{
		
		//soundSystem.PlaySound("Jump");
		//soundSystem.SetVolume("Jump", 0.5f);
		m_pBody->ApplyLinearImpulse(m_vJump, m_pBody->GetPosition(), true);
	}
}

void
FletchersPlayer::Draw(Renderer& renderer)
{
	m_pSprite->Draw(renderer);

}

