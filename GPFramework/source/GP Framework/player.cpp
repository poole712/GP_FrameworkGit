#include "player.h"

#include "renderer.h"
#include "animatedsprite.h"
#include "animatedentity.h"
#include "inputsystem.h"

Player::Player()
	: m_bSwitchingAnimation(false), m_bJumping(false), m_bFalling(false)
{
}

Player::~Player()
{
	delete m_iInputSystem;
	m_iInputSystem = 0;
}

bool Player::Initialise(Renderer& renderer)
{
	m_iInputSystem = new InputSystem();
	m_iInputSystem->Initialise();

	m_pASprite = renderer.CreateAnimatedSprite("sprites\\playersheet.png");
	m_pASprite->SetupFrames(48, 48);
	m_pASprite->SetFrameDuration(0.2f);
	m_pASprite->SetScale(2.66f);
	m_pASprite->SetLooping(false);

	AnimationRunning();

	m_pASprite->Animate();
	m_pASprite->SetLooping(true);
	
	return true;
}

void Player::Process(float deltaTime)
{
	if (m_bAlive)
	{
		m_pASprite->Process(deltaTime);

		if (IsKey1() && !m_bSwitchingAnimation && m_iActiveSpell != FIRE)
		{
			AnimateAnimationFire();
			m_iActiveSpell = FIRE;
		}
		
		if (IsKey2() && !m_bSwitchingAnimation && m_iActiveSpell != EARTH)
		{
			AnimateAnimationEarth();
			m_iActiveSpell = EARTH;
		}
		
		if (IsKey3() && !m_bSwitchingAnimation && m_iActiveSpell != ICE)
		{
			AnimateAnimationIce();
			m_iActiveSpell = ICE;
		}

		/*
		if (IsKeySpace() && !m_bSwitchingAnimation)
		{

		}
		*/

		if (!m_pASprite->IsAnimating() && m_bSwitchingAnimation)
		{
			AnimationRunning();
			m_bSwitchingAnimation = false;
		}
	}
}

void Player::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pASprite->Draw(renderer);
	}
}

bool Player::IsKey1()
{
	return (m_iInputSystem->GetKeyState(SDL_SCANCODE_1) == BS_PRESSED);
}

bool Player::IsKey2()
{
	return (m_iInputSystem->GetKeyState(SDL_SCANCODE_2) == BS_PRESSED);
}

bool Player::IsKey3()
{
	return (m_iInputSystem->GetKeyState(SDL_SCANCODE_3) == BS_PRESSED);
}

/*
bool Player::IsKeySpace()
{
	return (m_iInputSystem->GetKeyState(SDL_SCANCODE_SPACE) == BS_PRESSED);
}
*/

void Player::AnimationRunning()
{
	m_pASprite->SetLooping(true);
	m_pASprite->Animate();
	m_pASprite->SetAnimationRange(0, 7);
	m_pASprite->Restart();
}

/*
void Player::AnimationJump()
{
	m_pASprite->SetLooping(true);
	m_pASprite->SetAnimationRange(20, 21);
}

void Player::AnimationFall()
{
	m_pASprite->SetLooping(true);
	m_pASprite->SetAnimationRange(22, 23);
}
*/

void Player::AnimationFire()
{
	m_pASprite->SetAnimationRange(8, 11);
	m_pASprite->Restart();
}

void Player::AnimationEarth()
{
	m_pASprite->SetAnimationRange(12, 15);
	m_pASprite->Restart();
}

void Player::AnimationIce()
{
	m_pASprite->SetAnimationRange(16, 19);
	m_pASprite->Restart();
}

void Player::AnimateAnimationFire()
{
	m_pASprite->SetLooping(false);
	AnimationFire();
	m_bSwitchingAnimation = true;
}

void Player::AnimateAnimationEarth()
{
	m_pASprite->SetLooping(false);
	AnimationEarth();
	m_bSwitchingAnimation = true;
}

void Player::AnimateAnimationIce()
{
	m_pASprite->SetLooping(false);
	AnimationIce();
	m_bSwitchingAnimation = true;
}

/*
void Player::AnimateAnimationJump()
{
	AnimationJump();
	m_bSwitchingAnimation = true;
}

void Player::AnimateAnimationFall()
{
	AnimationFall();
	m_bSwitchingAnimation = true;
}
*/

ElementType Player::GetActiveSpell() const
{
	return m_iActiveSpell;
}