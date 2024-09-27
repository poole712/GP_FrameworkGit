#include "fletchersscene.h"

#include "fletchersplayer.h"
#include "fletchstestblock.h"
#include "soundsystem.h"
#include "box2d/box2d.h"

FletchersScene::FletchersScene()
{
}

FletchersScene::~FletchersScene()
{
	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_pWorld;
	m_pWorld = 0;

	delete m_pSoundSystem;
	m_pSoundSystem = 0;

	for (FletchsTestBlock* block : m_pTestBlocks)
	{
		delete block;
		block = 0;
	}
}

bool FletchersScene::Initialise(Renderer& renderer)
{

	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();

	//Physics
	b2Vec2 gravity;
	gravity.Set(0.0f, 100.0f);
	m_pWorld = new b2World(gravity);

	m_pPlayer = new FletchersPlayer();
	m_pPlayer->Initialise(renderer, m_pWorld);

	float currentX = 750;
	for (int i = 0; i < 10; i++)
	{
		FletchsTestBlock* newBlock = new FletchsTestBlock(currentX, 1000);
		currentX += 100;
		m_pTestBlocks.push_back(newBlock);
	}
	for (FletchsTestBlock* block : m_pTestBlocks)
	{
		block->Initialise(renderer);
	}

	return false;
}

void FletchersScene::Process(float deltaTime, InputSystem& inputSystem, int& scene)
{
	m_pWorld->Step(deltaTime, 6, 2);
	m_pSoundSystem->Process(deltaTime);
	m_pPlayer->Process(deltaTime, inputSystem, *m_pSoundSystem);
	for (FletchsTestBlock* block : m_pTestBlocks)
	{
		block->Process(deltaTime, inputSystem);
	}
}

void FletchersScene::Draw(Renderer& renderer)
{
	m_pPlayer->Draw(renderer);
	for (FletchsTestBlock* block : m_pTestBlocks)
	{
		block->Draw(renderer);
	}
}

void FletchersScene::DebugDraw()
{
}

