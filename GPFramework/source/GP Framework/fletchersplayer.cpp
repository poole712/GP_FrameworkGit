#define _CRT_SECURE_NO_WARNINGS


#include "fletchersplayer.h"

#include "logmanager.h"
#include "renderer.h"
#include "soundsystem.h"
#include "inputsystem.h"
#include "inlinehelper.h"
#include "box2d/box2d.h"
#include "fletchersscene.h"
#include "level.h"
#include "game.h"

#include <SDL_scancode.h>
#include <thread>
#include <chrono>
#include <string>


float FletchersPlayer::sm_fBoundaryWidth = 0.0f;
float FletchersPlayer::sm_fBoundaryHeight = 0.0f;

FletchersPlayer::FletchersPlayer()
	: m_fTimeSinceJumpStarted(0), m_bSwitchingAnimation(false), m_bJumping(false), m_bFalling(false)
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
	return true;
}

bool
FletchersPlayer::Initialise(Renderer& renderer, b2World& world, Level& scene)
{
	m_bUpdateWithVel = false;
	m_tFootstepCooldown = 0.75f;
	m_bAlive = true;

	m_vJump = b2Vec2(0, -100000.0f);
	//Setting up sprites
	m_pASprite = renderer.CreateAnimatedSprite("sprites\\playersheet.png");
	m_pASprite->SetupFrames(48, 48);
	m_pASprite->SetFrameDuration(0.2f);
	m_pASprite->SetScale(3.0f);
	m_pASprite->SetLooping(false);

	AnimationRunning();

	m_pASprite->Animate();
	m_pASprite->SetLooping(true);

	//Physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(m_vStartPos.x, m_vStartPos.y);
	m_pBody = world.CreateBody(&bodyDef);
	m_pBody->SetFixedRotation(true);
	m_pBody->SetGravityScale(0.5f);

	b2PolygonShape polyShape;
	polyShape.SetAsBox(30.0f, 30.0f);
	m_pShape = &polyShape;

	b2FixtureDef fixDef;
	fixDef.shape = &polyShape;
	fixDef.density = 0.05;
	fixDef.friction = 0.0f;
	fixDef.restitution = 0.0f;

	m_pFixture = m_pBody->CreateFixture(&fixDef);

	m_eCurrentType = FIRE;

	return true;
}

void
FletchersPlayer::Process(float deltaTime, InputSystem& inputSystem, SoundSystem& soundSystem, Level& scene)
{
	m_tFootstepTime += deltaTime;
	//m_pBody->ApplyForce(m_vVelocity, m_pBody->GetPosition(), true);
	m_pBody->SetTransform(b2Vec2(m_vStartPos.x, m_pBody->GetPosition().y), m_pBody->GetAngle());

	m_pASprite->SetX(m_pBody->GetPosition().x);
	m_pASprite->SetY(m_pBody->GetPosition().y - 35);

	m_position.x = m_pBody->GetPosition().x;
	m_position.y = m_pBody->GetPosition().y;

	m_pASprite->SetAngle(m_pBody->GetAngle());
	m_pASprite->Process(deltaTime);

	ButtonState key1State = inputSystem.GetKeyState(SDL_SCANCODE_1);
	ButtonState key2State = inputSystem.GetKeyState(SDL_SCANCODE_2);
	ButtonState key3State = inputSystem.GetKeyState(SDL_SCANCODE_3);

	if (key1State == BS_PRESSED)
	{
		m_eCurrentType = FIRE;
		AnimateAnimationFire();
		soundSystem.PlaySound("Fire");
		scene.ToggleBlocks(m_eCurrentType);
	}
	if (key2State == BS_PRESSED)
	{
		m_eCurrentType = EARTH;
		AnimateAnimationEarth();
		soundSystem.PlaySound("Earth");
		scene.ToggleBlocks(m_eCurrentType);
	}
	if (key3State == BS_PRESSED)
	{
		m_eCurrentType = ICE;
		AnimateAnimationIce();
		soundSystem.PlaySound("Ice");
		scene.ToggleBlocks(m_eCurrentType);
	}

	if (GetAnimatedPos().y > 1080)
	{
		Game::GetInstance().SwitchScene(2);
	}

	if (!m_pASprite->IsAnimating() && m_bSwitchingAnimation)
	{
		AnimationRunning();
		m_bSwitchingAnimation = false;
	}

	if (m_pBody->GetLinearVelocity().y == 0 && m_tFootstepTime >= m_tFootstepCooldown)
	{
		m_tFootstepTime = 0;
		int fsToPlay = GetRandom(0, 4);
		switch (fsToPlay)
		{
		case 0:
			soundSystem.PlaySound("Footstep0");
			break;
		case 1:
			soundSystem.PlaySound("Footstep1");
			break;
		case 2:
			soundSystem.PlaySound("Footstep2");
			break;
		case 3:
			soundSystem.PlaySound("Footstep3");
			break;
		case 4:
			soundSystem.PlaySound("Footstep4");
			break;
		}
	}
}

void 
FletchersPlayer::Process(float deltaTime, InputSystem& inputSystem)
{
}

void 
FletchersPlayer::AnimationRunning()
{
	m_pASprite->SetLooping(true);
	m_pASprite->Animate();
	m_pASprite->SetAnimationRange(0, 7);
	m_pASprite->Restart();
}

void
FletchersPlayer::Jump()
{
	m_pBody->ApplyLinearImpulseToCenter(m_vJump, true);
}

ElementType
FletchersPlayer::GetType() const
{
	return m_eCurrentType;
}

void
FletchersPlayer::Jump(SoundSystem& soundSystem)
{
	m_pBody->ApplyLinearImpulse(m_vJump, m_pBody->GetPosition(), true);
	soundSystem.PlaySound("Bounce");
}

void 
FletchersPlayer::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pASprite->Draw(renderer);
	}
}

void FletchersPlayer::AnimationFire()
{
	m_pASprite->SetAnimationRange(8, 11);
	m_pASprite->Restart();
}

void FletchersPlayer::AnimationEarth()
{
	m_pASprite->SetAnimationRange(12, 15);
	m_pASprite->Restart();
}

void FletchersPlayer::AnimationIce()
{
	m_pASprite->SetAnimationRange(16, 19);
	m_pASprite->Restart();
}

void FletchersPlayer::AnimateAnimationFire()
{
	m_pASprite->SetLooping(false);
	AnimationFire();
	m_bSwitchingAnimation = true;
}

void FletchersPlayer::AnimateAnimationEarth()
{
	m_pASprite->SetLooping(false);
	AnimationEarth();
	m_bSwitchingAnimation = true;
}

void FletchersPlayer::AnimateAnimationIce()
{
	m_pASprite->SetLooping(false);
	AnimationIce();
	m_bSwitchingAnimation = true;
}

