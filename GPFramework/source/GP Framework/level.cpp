//This
#include "level.h"

//Libraries
#include "entity.h"
#include "box2d/box2d.h"
#include "soundsystem.h"

using namespace std;

Level::Level()
{

}

Level::~Level()
{
	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		delete (*it);
		(*it) = 0;
		++it;
	}

	delete m_pSoundSystem;
	m_pSoundSystem = 0;

	delete m_pWorld;
	m_pWorld = 0;
}

bool
Level::Initialise(Renderer& renderer, vector<Entity*> entityList)
{
	//Sound System
	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();

	//Physics
	b2Vec2 gravity;
	gravity.Set(0.0f, 100.0f);
	m_pWorld = new b2World(gravity);

	m_entityList = entityList;

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		(*it)->Initialise(renderer, *m_pWorld);
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
		(*it)->Process(deltaTime, inputSystem);
		++it;
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
}

void
Level::DebugDraw()
{

}