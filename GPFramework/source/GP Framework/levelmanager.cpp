//This
#include "levelmanager.h"

//Local
#include "levelparser.h"
#include "level.h"
#include "entity.h"
#include "imgui/imgui.h"

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

}

bool
LevelManager::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

	LevelParser::GetInstance().LoadLevelFile("data\\testmapdata.ini");
	m_pLevelData = LevelParser::GetInstance().GetLevelData();
	LevelParser::GetInstance().SetTileSize(128.0f);
	
	auto firstLevel = m_pLevelData->begin();
	LoadLevel(firstLevel->first);

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
LevelManager::LoadLevel(const string& level)
{
	//Delete Level
	UnloadLevel();

	//Load new Level
	m_pActiveLevel = new Level();
	vector<Entity*> entityList = LevelParser::GetInstance().LoadLevel(level, *m_pRenderer);
	m_pActiveLevel->Initialise(*m_pRenderer, entityList);
}

void LevelManager::UnloadLevel()
{
	if (m_pActiveLevel != nullptr)
	{
		delete m_pActiveLevel;
		m_pActiveLevel = 0;
	}
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