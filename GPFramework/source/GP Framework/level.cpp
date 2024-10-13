//This
#include "level.h"

//Libraries
#include <typeinfo>
#include "entity.h"
#include "fletchstestblock.h"
#include "fletchersplayer.h"
#include "box2d/box2d.h"
#include "soundsystem.h"
#include "renderer.h"
#include "hud.h"

using namespace std;

Level::Level()
{

}

Level::~Level()
{
	delete m_pSoundSystem;
	m_pSoundSystem = 0;

	delete m_pWorld;
	m_pWorld = 0;

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		delete (*it);
		(*it) = 0;
		++it;
	}

	/*delete m_pPlayer;
	m_pPlayer = 0;*/
}


bool
Level::Initialise(Renderer& renderer, vector<Entity*> entityList)
{
	//Sound System
	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();
	m_pSoundSystem->CreateSound("sounds\\GameMusic.mp3", "Game Music");
	m_pSoundSystem->CreateSound("sounds\\Earth.mp3", "Earth");
	m_pSoundSystem->CreateSound("sounds\\Ice.mp3", "Ice");
	m_pSoundSystem->CreateSound("sounds\\Fire.mp3", "Fire");
	m_pSoundSystem->CreateSound("sounds\\Bounce.wav", "Bounce");

	m_pSoundSystem->CreateSound("sounds\\Footstep0.mp3", "Footstep0");
	m_pSoundSystem->CreateSound("sounds\\Footstep1.mp3", "Footstep1");
	m_pSoundSystem->CreateSound("sounds\\Footstep2.mp3", "Footstep2");
	m_pSoundSystem->CreateSound("sounds\\Footstep3.mp3", "Footstep3");
	m_pSoundSystem->CreateSound("sounds\\Footstep4.mp3", "Footstep4");


	//Hud
	m_pHud = new Hud();
	m_pHud->Initialise(renderer);

	//Physics
	b2Vec2 gravity;
	gravity.Set(0.0f, 100.0f);
	m_pWorld = new b2World(gravity);

	m_entityList = entityList;

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		(*it)->Initialise(renderer, *m_pWorld, *this);
		if ((*it)->GetElementType() == PLAYER)
		{
			m_pPlayer = static_cast<FletchersPlayer*>((*it));
		}
		++it;
	}

	return true;
}


void
Level::BeginPlay()
{
	m_pSoundSystem->PlaySound("Game Music");
}


void
Level::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pWorld->Step(deltaTime, 5, 8);

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		(*it)->Process(deltaTime, inputSystem, *m_pSoundSystem, *this);
		++it;
	}
	m_pHud->Process(deltaTime, inputSystem);
	CheckCollisions();
}

void 
Level::CheckCollisions()
{
	for (Entity* entity : m_entityList)
	{
		if (m_pPlayer->IsAnimationCollidingWith(*entity) && entity->GetElementType() == TRAMP && entity->IsAlive())
		{
			m_pPlayer->Jump(*m_pSoundSystem);
			entity->SetAliveState(false);
		}
	}
}

void
Level::Draw(Renderer& renderer)
{
	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		(*it)->Draw(renderer);
		++it;
	}
	m_pHud->Draw(renderer);
}

void
Level::DebugDraw()
{

}

void 
Level::ToggleBlocks(ElementType type)
{
	for (Entity* block : m_entityList)
	{
		block->Toggle(type);
	}
	//m_pTestTramp->Toggle(type);
}