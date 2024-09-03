#include "scenespaceinvadersclone.h"

#include "renderer.h"
#include "imgui/imgui.h"
#include "logmanager.h"
#include "inputsystem.h"
#include "lasercannon.h"
#include "particleemitter.h"
#include "invader.h"
#include "soundsystem.h"

#include <SDL_scancode.h>

#include <cassert>
#include <cstdlib>

SceneSpaceInvadersClone::SceneSpaceInvadersClone()
	: m_iShowCount(55), m_pLaserCannon(0), m_pSoundSystem(0), m_pParticleEmitter(0)
{

}

SceneSpaceInvadersClone::~SceneSpaceInvadersClone()
{
	delete m_pLaserCannon;
	m_pLaserCannon = 0;
	delete m_pSoundSystem;
	m_pSoundSystem = 0;
	for (Invader* invader : m_pInvaders)
	{
		delete invader;
		invader = 0;
	}
}

bool
SceneSpaceInvadersClone::Initialise(Renderer& renderer)
{
	SoundSystem* soundSystem = 0;
	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();
	m_pSoundSystem->CreateSound("sounds\\Land.wav", "Land");

	LaserCannon* laserCannon = 0;
	m_pLaserCannon = new LaserCannon();
	m_pLaserCannon->Initialise(renderer);
	m_pLaserCannon->SetAliveState(true);

	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->Initialise(renderer);

	float invaderYOffset = 100;
	float invaderXOffset = 450;
	for (int i = 0; i < 55; i++)
	{
		if (i % 11 == 0)
		{
			invaderYOffset += 40;
			invaderXOffset = 450;
		}
		invaderXOffset += 30;
		Invader* newInvader = new Invader();
		newInvader->SetPosition(invaderXOffset, invaderYOffset);
		newInvader->SetAliveState(true);
		
		m_pInvaders.push_back(newInvader);
	}
	for (Invader* invader : m_pInvaders)
	{
		invader->Initialise(renderer);
		invader->SetPlayerRef(*m_pLaserCannon);
	}
	return true;

}

void
SceneSpaceInvadersClone::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pLaserCannon->Process(deltaTime, inputSystem);
	m_pSoundSystem->Process(deltaTime);
	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));
	ButtonState leftArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_LEFT));
	ButtonState rightArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_RIGHT));

	m_pParticleEmitter->Process(deltaTime);

	if (leftArrowState == BS_PRESSED && rightArrowState == BS_NEAUTRAL && m_pLaserCannon->GetPosition().x > 450.0f)
	{
		m_pLaserCannon->Move(-50.0f);
	}
	if (spaceState == BS_RELEASED)
	{
		m_pLaserCannon->ShootBullet(*m_pSoundSystem);
		m_pParticleEmitter->SetPosition(m_pLaserCannon->GetPosition().x, m_pLaserCannon->GetPosition().y - 25.0f);
		m_pParticleEmitter->Spawn();
		LogManager::GetInstance().Log("Space key released.");
	}
	if (rightArrowState == BS_PRESSED && leftArrowState == BS_NEAUTRAL && m_pLaserCannon->GetPosition().x < 830.0f)
	{
		m_pLaserCannon->Move(50.0f);
	}
	else if (leftArrowState == BS_RELEASED || rightArrowState == BS_RELEASED)
	{
		m_pLaserCannon->Move(0.0f);
	}
	if (m_pLaserCannon->GetPosition().x - 50.0f < 450.0f && rightArrowState == BS_NEAUTRAL)
	{
		m_pLaserCannon->Move(0.0f);
	}
	if (m_pLaserCannon->GetPosition().x + 50.0f > 830.0f && leftArrowState == BS_NEAUTRAL)
	{
		m_pLaserCannon->Move(0.0f);
	}

	for (Invader* invader : m_pInvaders)
	{
		invader->Process(deltaTime, inputSystem);
		if (m_pLaserCannon->GetCurrentBullet()->IsCollidingWith(*invader))
		{
			LogManager::GetInstance().Log("Hit invader");
			invader->SetAliveState(false);
			m_pLaserCannon->GetCurrentBullet()->SetAliveState(false);
		}
	}
}

void
SceneSpaceInvadersClone::Draw(Renderer& renderer)
{
	m_pLaserCannon->Draw(renderer);
	m_pParticleEmitter->Draw(renderer);
	for (int i = 0; i < m_iShowCount; i++)
	{
		m_pInvaders[i]->Draw(renderer);
	}
}

void
SceneSpaceInvadersClone::DebugDraw()
{
	ImGui::Text("Scene: Bouncing Balls");

	ImGui::SliderInt("Show count", &m_iShowCount, 1, 55);

	static int editBallNumber = 0;
	ImGui::SliderInt("Edit ball", &editBallNumber, 0, 99);

	
}