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
#include "levelmanager.h"

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

	delete m_pHud;
	m_pHud = 0;

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		delete (*it);
		(*it) = 0;
		++it;
	}
}

bool
Level::Initialise(Renderer& renderer, vector<Entity*> entityList, LevelManager& levelManager)
{
	//Manager
	m_pLevelManager = &levelManager;

	//Sound System
	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();

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
			m_pPlayer->Jump();
			entity->SetAliveState(false);
		}

		if (m_pPlayer->IsAnimationCollidingWith(*entity) && entity->GetElementType() == FLAG && entity->IsAlive())
		{
			m_pLevelManager->NextLevel();
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
}