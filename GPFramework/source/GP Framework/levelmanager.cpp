//This
#include "levelmanager.h"

//Local
#include "levelparser.h"
#include "level.h"
#include "entity.h"
#include "imgui/imgui.h"
#include "logmanager.h"

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
}

bool
LevelManager::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

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
	vector<Entity*> entityList = LevelParser::GetInstance().LoadLevel(level, *m_pRenderer);
	m_pActiveLevel->Initialise(*m_pRenderer, entityList, *this);
	LevelParser::GetInstance().m_pLevelString = level;
}

void
LevelManager::ResetLevel()
{
	LoadLevel(LevelParser::GetInstance().m_pLevelString);
}

void LevelManager::UnloadLevel()
{
	delete m_pActiveLevel;
	m_pActiveLevel = 0;
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