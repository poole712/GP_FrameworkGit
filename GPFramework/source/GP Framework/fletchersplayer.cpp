#define _CRT_SECURE_NO_WARNINGS


#include "fletchersplayer.h"

#include "logmanager.h"
#include "renderer.h"
#include "sprite.h"
#include "soundsystem.h"
#include "inputsystem.h"
#include "box2d/box2d.h"

#include <SDL_scancode.h>
#include <thread>
#include <chrono>


float FletchersPlayer::sm_fBoundaryWidth = 0.0f;
float FletchersPlayer::sm_fBoundaryHeight = 0.0f;

FletchersPlayer::FletchersPlayer()
	: m_fTimeSinceJumpStarted(0)
{
}

FletchersPlayer::~FletchersPlayer()
{
	
}

bool
FletchersPlayer::Initialise(Renderer& renderer)
{
	m_pSprite = renderer.CreateSprite("sprites\\ball.png");

	return true;
}

bool
FletchersPlayer::Initialise(Renderer& renderer, b2World* world)
{
	m_fJumpStrength = -600.0f;

	//Setting up sprites
	m_pSprite = renderer.CreateSprite("sprites\\UprightBB.png");
	m_pSprite->SetScale(1.25f);

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

	return true;
}

void
FletchersPlayer::Process(float deltaTime, InputSystem& inputSystem, SoundSystem& soundSystem)
{
	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);

	m_position.x = m_pBody->GetPosition().x;
	m_position.y = m_pBody->GetPosition().y;

	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));

	if (spaceState == BS_PRESSED)
	{
		Jump(soundSystem);
	}
}

void FletchersPlayer::Process(float deltaTime, InputSystem& inputSystem)
{
}


void
FletchersPlayer::Jump(SoundSystem& soundSystem)
{
	if (m_pBody->GetPosition().y <= 605 && m_pBody->GetPosition().y >= 595)
	{
		b2Vec2 jumpVec = b2Vec2(0, m_fJumpStrength);
		soundSystem.PlaySound("Jump");
		soundSystem.SetVolume("Jump", 0.5f);
		m_pBody->ApplyLinearImpulse(jumpVec, m_pBody->GetPosition(), true);
	}
}

void
FletchersPlayer::Draw(Renderer& renderer)
{
	m_pSprite->Draw(renderer);

}
