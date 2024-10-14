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
#include "logmanager.h"
#include "game.h"
#include <cmath>

using namespace std;

Level::Level()
{

}

Level::~Level()
{
	delete m_pWorld;
	m_pWorld = 0;

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		delete (*it);
		(*it) = 0;
	}

	delete m_pHud;
	m_pHud = 0;
}


bool
Level::Initialise(Renderer& renderer)
{
	//Manager
	m_pLevelManager = new LevelManager();

	m_pSoundSystem = new SoundSystem();

	//Hud
	m_pHud = new Hud();
	m_pHud->Initialise(renderer);

	//Physics
	b2Vec2 gravity;
	gravity.Set(0.0f, 100.0f);
	m_pWorld = new b2World(gravity);

	FletchsTestBlock* test = new FletchsTestBlock(1920, 600, NONE);
	test->Initialise(renderer, *m_pWorld);
	m_entityList.push_back(test);

	BeginPlay();
	m_bSwitching = false;

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

		if ((*it)->GetPosition().x < (1920 / 2))
		{
			Game::GetInstance().SwitchScene(2);
		}
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
		if (m_pPlayer->IsAnimationCollidingWith(*entity) && entity->IsAlive())
		{
			if (entity->GetElementType() == TRAMP)
			{
				m_pPlayer->Jump(*m_pSoundSystem);
				entity->SetAliveState(false);
			}
			else if (entity->GetElementType() == FLAG)
			{
				m_pLevelManager->NextLevel();
				entity->SetAliveState(false);
				return;
			}
			else
			{
				LogManager::GetInstance().Log("No Flag");
			}
		}
	}
}

bool
Level::CollidingWith(Entity& entityA, Entity& entityB)
{
	if (entityA.IsAlive())
	{
		if (entityB.IsAlive())
		{
			// Corrected distance calculation
			float dx = entityB.GetPosition().x - entityA.GetPosition().x;
			float dy = entityB.GetPosition().y - entityA.GetPosition().y;

			// Calculate the squared distance
			float distanceSquared = dx * dx + dy * dy;

			// Calculate the actual distance
			float distance = std::sqrt(distanceSquared);

			// Calculate the squared sum of radii
			float radiiSum = 100;
			float radiiSumSquared = radiiSum * radiiSum;

			// Return if the squared distance is less than or equal to the squared sum of radii
			LogManager::GetInstance().Log(to_string(distanceSquared <= radiiSumSquared).c_str());
			return distanceSquared <= radiiSumSquared;
		}
	}
	return false;
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