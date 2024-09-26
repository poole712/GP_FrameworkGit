#include "fletchersscene.h"

#include "entity.h"
#include "fletchersplayer.h"

FletchersScene::FletchersScene()
{
}

FletchersScene::~FletchersScene()
{
}

bool FletchersScene::Initialise(Renderer& renderer)
{
	m_pPlayer = new FletchersPlayer();
	m_pPlayer->Initialise(renderer);

	return false;
}

void FletchersScene::Process(float deltaTime, InputSystem& inputSystem, int& scene)
{
	m_pPlayer->Process(deltaTime, inputSystem);
}

void FletchersScene::Draw(Renderer& renderer)
{
	m_pPlayer->Draw(renderer);
}

void FletchersScene::DebugDraw()
{
}

