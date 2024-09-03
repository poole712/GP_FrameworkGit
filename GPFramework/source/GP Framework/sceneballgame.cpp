#include "sceneballgame.h"

SceneBallGame::SceneBallGame()
{

}

SceneBallGame::~SceneBallGame()
{
	for (Ball* ball : m_pGoodBalls)
	{
		delete ball;
		ball = 0;
	}
	for (Ball* ball : m_pBadBalls)
	{
		delete ball;
		ball = 0;
	}
	delete m_pPlayerBall;
	m_pPlayerBall = 0;
}

bool
SceneBallGame::Initialise(Renderer& renderer)
{



	return true;
}

void 
SceneBallGame::Process(float deltaTime, InputSystem& inputSystem)
{

}

void
SceneBallGame::Draw(Renderer& renderer)
{

}

void 
SceneBallGame::DebugDraw()
{

}