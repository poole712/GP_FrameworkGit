//This
#include "levelmanager.h"

//Local
#include "levelparser.h"
#include "level.h"
#include "entity.h"
#include "imgui/imgui.h"
#include "logmanager.h"
#include "soundsystem.h"

//Libraries
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

LevelManager::LevelManager() 
	: m_pLevelData(new std::map<string, std::map<int, string>>())
	, m_pActiveLevel (0)
{

}

LevelManager::~LevelManager()
{
	delete m_pActiveLevel;
	m_pActiveLevel = 0;

	delete m_pSoundSystem;
	m_pSoundSystem = 0;
}

bool
LevelManager::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();
	InitialiseSounds();

	m_pLevelData = LevelParser::GetInstance().GetLevelData();
	LevelParser::GetInstance().SetTileSize(128.0f);
	
	LoadLevel(LevelParser::GetInstance().m_pLevelString);

	return true;
}

void
LevelManager::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pActiveLevel->Process(deltaTime, inputSystem);
}

void
LevelManager::Draw(Renderer& renderer)
{
	m_pActiveLevel->Draw(renderer);
}

void
LevelManager::NextLevel()
{
	auto levelIt = m_pLevelData->find(LevelParser::GetInstance().m_pLevelString);
	
	if (levelIt != m_pLevelData->end())
	{
		++levelIt;
		if (levelIt != m_pLevelData->end())
		{
			LogManager::GetInstance().Log(levelIt->first.c_str());
			LoadLevel(levelIt->first);
		}
		else
		{
			//End Game
			LogManager::GetInstance().Log("End of Game");
		}
	}
	else
	{
		//End Game
		LogManager::GetInstance().Log("End of Game");
	}
}

void
LevelManager::LoadLevel(const string& level)
{
	//Delete Level
	UnloadLevel();

	//Load new Level
	m_pActiveLevel = new Level();
	m_EntityList = LevelParser::GetInstance().LoadLevel(level, *m_pRenderer);
	m_pActiveLevel->Initialise(*m_pRenderer, m_EntityList, *this, *m_pSoundSystem);
	LevelParser::GetInstance().m_pLevelString = level;
}

void
LevelManager::ResetLevel()
{
	LoadLevel(LevelParser::GetInstance().m_pLevelString);
}

void LevelManager::UnloadLevel()
{
	for (auto it = m_EntityList.begin(); it != m_EntityList.end();)
	{
		delete (*it);
		(*it) = nullptr;
		++it;
	}

	delete m_pSoundSystem;
	m_pSoundSystem = 0;
	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();
	InitialiseSounds();

	delete m_pActiveLevel;
	m_pActiveLevel = 0;
}

void 
LevelManager::InitialiseSounds()
{
	m_pSoundSystem->CreateSound("sounds\\GameMusic.mp3", "Game Music");
	m_pSoundSystem->CreateSound("sounds\\Earth.mp3", "Earth");
	m_pSoundSystem->CreateSound("sounds\\Ice.mp3", "Ice");
	m_pSoundSystem->CreateSound("sounds\\Fire.mp3", "Fire");
	m_pSoundSystem->CreateSound("sounds\\Bounce.wav", "Bounce");

	m_pSoundSystem->CreateSound("sounds\\Footstep0.mp3", "Footstep0");
	m_pSoundSystem->CreateSound("sounds\\Footstep1.mp3", "Footstep1");
	m_pSoundSystem->CreateSound("sounds\\Footstep2.mp3", "Footstep2");
	m_pSoundSystem->CreateSound("sounds\\Footstep3.mp3", "Footstep3");
	m_pSoundSystem->CreateSound("sounds\\Footstep4.mp3", "Footstep4");
}


void
LevelManager::DebugDraw()
{
	for (const auto& section : *m_pLevelData)
	{
		if (ImGui::Button(section.first.c_str()))
		{
			LoadLevel(section.first);
		}
	}
}