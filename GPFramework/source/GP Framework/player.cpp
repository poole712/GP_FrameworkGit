#include "player.h"

#include "renderer.h"
#include "animatedsprite.h"
#include "animatedentity.h"
#include "inputsystem.h"

Player::Player()
	: m_bSwitchingAnimation(false)
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

	m_pASprite = renderer.CreateAnimatedSprite("sprites\\anim8strip.png");
	m_pASprite->SetupFrames(64, 64);
	m_pASprite->SetFrameDuration(0.2f);
	m_pASprite->SetScale(1.0f);
	m_pASprite->SetLooping(false);

	AnimationCount0to3();

	m_pASprite->Animate();
	m_pASprite->SetLooping(true);
	
	return true;
}

void Player::Process(float deltaTime)
{
	if (m_bAlive)
	{
		m_pASprite->Process(deltaTime);

		if (IsKey1() && !m_bSwitchingAnimation && m_iActiveSpell != 1)
		{
			AnimateAnimation1();
			m_iActiveSpell = 1;
		}
		
		if (IsKey2() && !m_bSwitchingAnimation && m_iActiveSpell != 2)
		{
			AnimateAnimation2();
			m_iActiveSpell = 2;
		}
		
		if (IsKey3() && !m_bSwitchingAnimation && m_iActiveSpell != 3)
		{
			AnimateAnimation3();
			m_iActiveSpell = 3;
		}

		if (!m_pASprite->IsAnimating() && m_bSwitchingAnimation)
		{
			AnimationCount0to3();
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

void Player::AnimationCount0to3()
{
	m_pASprite->SetLooping(true);
	m_pASprite->Animate();
	m_pASprite->SetAnimationRange(0, 3);
	m_pASprite->Restart();
}

void Player::AnimationCount4to5()
{
	m_pASprite->SetAnimationRange(4, 5);
	m_pASprite->Restart();
}

void Player::AnimationCount5to6()
{
	m_pASprite->SetAnimationRange(5, 6);
	m_pASprite->Restart();
}

void Player::AnimationCount6to7()
{
	m_pASprite->SetAnimationRange(6, 7);
	m_pASprite->Restart();
}

void Player::AnimateAnimation1()
{
	m_pASprite->SetLooping(false);
	AnimationCount4to5();
	m_bSwitchingAnimation = true;
}

void Player::AnimateAnimation2()
{
	m_pASprite->SetLooping(false);
	AnimationCount5to6();
	m_bSwitchingAnimation = true;
}

void Player::AnimateAnimation3()
{
	m_pASprite->SetLooping(false);
	AnimationCount6to7();
	m_bSwitchingAnimation = true;
}
