#include "fletchersscene.h"

#include "fletchersplayer.h"
#include "fletchstestblock.h"
#include "soundsystem.h"
#include "box2d/box2d.h"
#include "game.h"

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

	delete m_pSingleBlock;
	m_pSingleBlock = 0;
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
	for (int i = 0; i < 5; i++)
	{
		FletchsTestBlock* newBlock = new FletchsTestBlock(currentX, 1000, ICE);
		currentX += 125;
		m_pTestBlocks.push_back(newBlock);
	}
	for (FletchsTestBlock* block : m_pTestBlocks)
	{
		block->Initialise(m_pWorld ,renderer);
	}
	m_pSingleBlock = new FletchsTestBlock(1100, 950, EARTH);
	m_pSingleBlock->Initialise(m_pWorld, renderer);

	return false;
}

void FletchersScene::Process(float deltaTime, InputSystem& inputSystem, Game& game)
{
	m_pWorld->Step(deltaTime, 5, 8);
	m_pSoundSystem->Process(deltaTime);
	m_pPlayer->Process(deltaTime, inputSystem, *m_pSoundSystem);
	m_pSingleBlock->Process(deltaTime, inputSystem);

	for (FletchsTestBlock* block : m_pTestBlocks)
	{
		block->Process(deltaTime, inputSystem);
	}
	if (m_pPlayer->GetPosition().y > 1080)
	{
		game.SwitchScene(3);
	}
	if (m_pPlayer->IsCollidingWith(*m_pSingleBlock) && m_pPlayer->GetPosition().y > m_pSingleBlock->GetPosition().y - 50)
	{
		game.SwitchScene(3);
	}

}

void FletchersScene::Draw(Renderer& renderer)
{
	m_pPlayer->Draw(renderer);
	m_pSingleBlock->Draw(renderer);
	for (FletchsTestBlock* block : m_pTestBlocks)
	{
		block->Draw(renderer);
	}
}

void FletchersScene::DebugDraw()
{
}

