//This
#include "scenesplashscreen.h"

//Include
#include "renderer.h"
#include "sprite.h"
#include "game.h"

SceneSplashscreen::SceneSplashscreen()
{

}

SceneSplashscreen::~SceneSplashscreen()
{
	delete m_pAutLogo;
	m_pAutLogo = 0;


	delete m_pFmodLogo;
	m_pFmodLogo = 0;
}

bool
SceneSplashscreen::Initialise(Renderer& renderer)
{
	renderer.SetClearColour(0, 0, 0);

	m_pAutLogo = renderer.CreateSprite("..\\game\\sprites\\AUT-logo-block.png");
	m_pFmodLogo = renderer.CreateSprite("..\\game\\sprites\\FMOD_Logo_White_Black_Background.png");

	//Set Positions
	m_pAutLogo->SetX(renderer.GetWidth() / 2);
	m_pAutLogo->SetY(renderer.GetHeight() / 2);

	m_pFmodLogo->SetX(renderer.GetWidth() / 2);
	m_pFmodLogo->SetY(renderer.GetHeight() / 2);

	//Set Alpha
	m_pAutLogo->SetAlpha(0);
	m_pFmodLogo->SetAlpha(0);

	m_currentLogo = AUT;
	m_fTime = 5.0f;
	m_fFrameTime = 0.016f;

	return true;
}

void
SceneSplashscreen::Process(float deltaTime, InputSystem& inputSystem, Game& game)
{
	m_fTimeElapsed += deltaTime;
	m_fTotalTime += deltaTime;

	if (m_fTimeElapsed >= (m_fFrameTime))
	{
		switch (m_currentLogo)
		{
		case AUT:
			m_pAutLogo->SetAlpha(m_pAutLogo->GetAlpha() + (0.016f));
			if (m_fTotalTime >= m_fTime)
			{
				m_currentLogo = F_MOD;
				m_fTotalTime = 0;
			}
			break;
		case F_MOD:
			m_pFmodLogo->SetAlpha(m_pFmodLogo->GetAlpha() + (0.016f));
			m_fTimeElapsed = 0;
			if (m_fTotalTime >= m_fTime)
			{
				m_currentLogo = DONE;
				m_fTotalTime = 0;
			}
			break;
		case DONE:
			Game::GetInstance().SwitchScene(0);
		}
		m_fTimeElapsed = 0;
	}
}

void
SceneSplashscreen::Draw(Renderer& renderer)
{
	switch (m_currentLogo)
	{
	case AUT:
		m_pAutLogo->Draw(renderer);
		break;
	case F_MOD:
		m_pFmodLogo->Draw(renderer);
		break;
	}
}

void
SceneSplashscreen::DebugDraw()
{

}

