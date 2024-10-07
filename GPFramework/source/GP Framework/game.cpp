//This include:
#include "game.h"

//Library include
#include "renderer.h"
#include "logmanager.h"
#include "sprite.h"
#include "stdlib.h"
#include "time.h"

#include "imgui/imgui_impl_sdl2.h"
#include "levelparser.h"
#include "inputsystem.h"
#include "xboxcontroller.h"

#include "scenebbmainmenu.h"
#include "sceneplayeranimation.h"
#include "fletchersscene.h"
#include "scenedeathmenu.h"
#include "levelmanager.h"


//Static members:
Game* 
Game::sm_pInstance = 0;

Game& 
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pRenderer(0)
	, m_bLooping(true)
	, m_bShowDebugWindow(true)
	
{

}

Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;
}

void
Game::Quit()
{
	m_bLooping = false;
}

bool
Game::Initialise()
{
	int bbWidth = 1920;
	int bbHeight = 1080;

	m_pRenderer = new Renderer();
	if (!m_pRenderer->Initialise(true, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}

	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();
	m_iLastTime = SDL_GetPerformanceCounter();

	m_pInputSystem = new InputSystem();
	m_pInputSystem->Initialise();

	m_pInputSystem->ShowMouseCursor(m_bShowDebugWindow);

	
	//Scene* pScene = 0;

	//pScene = new SceneBBMainMenu();
	//pScene->Initialise(*m_pRenderer);
	//m_scenes.push_back(pScene);

	Scene* pLevelTest = 0;
	pLevelTest = new LevelManager();
	pLevelTest->Initialise(*m_pRenderer);
	m_scenes.push_back(pLevelTest);

	Scene* pGameScene = 0;
	pGameScene = new FletchersScene();
	pGameScene->Initialise(*m_pRenderer);
	m_scenes.push_back(pGameScene);

	//Scene* pAnimScene = new ScenePlayerAnimation();
	//pAnimScene->Initialise(*m_pRenderer);
	//m_scenes.push_back(pAnimScene);

	Scene* pDeathScene = new SceneDeathMenu();
	pDeathScene->Initialise(*m_pRenderer);
	m_scenes.push_back(pDeathScene);

	m_iCurrentScene = 0;

	m_pRenderer->SetClearColour(100, 100, 100);

	return true;
}

void 
Game::SwitchScene(int scene)
{
	//Re-initialise game scene
	if (scene == 1)
	{
		m_scenes[1]->Initialise(*m_pRenderer);
	}
	m_iCurrentScene = scene;
}



bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	m_pInputSystem->ProcessInput();

	if (m_bLooping)
	{
		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_iLastTime = current;

		m_fExecutionTime += deltaTime;

		Process(deltaTime);

#ifdef USE_LAG
		m_fLag += deltaTime;

		int innerLag = 0;

		while (m_fLag >= stepSize)
		{
			Process(stepSize);

			m_fLag -= stepSize;

			++m_iUpdateCount;
			++innerLag;
		}
#endif // USE_LAG

		Draw(*m_pRenderer);
	}

	return m_bLooping;
}

void
Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);
	// TODO: Add game objects to process here!
	m_scenes[m_iCurrentScene]->Process(deltaTime, *m_pInputSystem, *this);
}

void 
Game::Draw(Renderer& renderer)
{
	++m_iFrameCount;

	renderer.Clear();
	DebugDraw();

	//TODO: Add game objects to draw here!
	m_scenes[m_iCurrentScene]->Draw(renderer);

	renderer.Present();
}

void
Game::ProcessFrameCounting(float deltaTime)
{
	//Count total simulation time elapsed:
	m_fElapsedSeconds += deltaTime;

	//Frame Counters
	if (m_fElapsedSeconds > 1.0f)
	{
		m_fElapsedSeconds -= 1.0f;
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}

}

void 
Game::ToggleDebugWindow()
{
	m_bShowDebugWindow = !m_bShowDebugWindow;
}

void
Game::DebugDraw()
{

	if (m_bShowDebugWindow)
	{
		bool open = true;

		ImGui::Begin("Debug Window", &open, ImGuiWindowFlags_MenuBar);


		ImGui::Text("COMP710 GP Framework (%s)", "2024, S2");

		if (ImGui::Button("Quit"))
		{
			Quit();
		}

		ImGui::SliderInt("Active scene", &m_iCurrentScene, 0, m_scenes.size() - 1, "%d");

		m_scenes[m_iCurrentScene]->DebugDraw();

		ImGui::End();
		
	}


}