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
	delete m_pWorld;
	m_pWorld = 0;

	delete m_pHud;
	m_pHud = 0;
}


bool
Level::Initialise(Renderer& renderer, vector<Entity*>& entityList, LevelManager& levelManager, SoundSystem& soundSystem)
{
	//Manager
	m_pLevelManager = &levelManager;

	m_pSoundSystem = &soundSystem;

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

	BeginPlay();

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
	if (m_pPlayer == nullptr) { return; }

	for (Entity* entity : m_entityList)
	{
		if (entity == nullptr) { continue; }

		if (m_pPlayer->IsAnimationCollidingWith(*entity) && entity->IsAlive())
		{
			if (entity->GetElementType() == TRAMP)
			{
				if (entity == nullptr) { continue; }
				m_pPlayer->Jump(*m_pSoundSystem);
				entity->SetAliveState(false);
			}
			else if (entity->GetElementType() == FLAG)
			{
				if (entity == nullptr) { continue; }
				m_pLevelManager->NextLevel();
				entity->SetAliveState(false);
			}
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