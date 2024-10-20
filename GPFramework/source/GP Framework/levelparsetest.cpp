//This
#include "levelparsetest.h"

//Include
#include "entity.h"
#include "levelparser.h"
#include "box2d/box2d.h"
#include "soundsystem.h"

using namespace std;

LevelParseTest::LevelParseTest()
{

}

LevelParseTest::~LevelParseTest()
{
	delete m_pWorld;
	m_pWorld = nullptr;

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		delete (*it);
		(*it) = nullptr;
		++it;
	}
}

bool
LevelParseTest::Initialise(Renderer& renderer)
{
	return Initialise(renderer, "[level1]");
}

bool
LevelParseTest::Initialise(Renderer& renderer, const string& levelname)
{
	//Sound System
	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();

	//Physics
	b2Vec2 gravity;
	gravity.Set(0.0f, 100.0f);
	m_pWorld = new b2World(gravity);

	//Level
	LevelParser::GetInstance().SetTileSize(128.0f);
	m_entityList = LevelParser::GetInstance().LoadLevel(levelname);

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		(*it)->Initialise(renderer, *m_pWorld);
		++it;
	}

	return true;
}

void
LevelParseTest::Process(float deltaTime, InputSystem& inputSystem, Game& game)
{
	m_pWorld->Step(deltaTime, 5, 8);

	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		(*it)->Process(deltaTime, inputSystem);
		++it;
	}
}

void
LevelParseTest::Draw(Renderer& renderer)
{
	for (auto it = m_entityList.begin(); it != m_entityList.end();)
	{
		(*it)->Draw(renderer);
		++it;
	}
}

void 
LevelParseTest::DebugDraw()
{

}