//This
#include "levelparser.h"

//Local
#include "logmanager.h"
#include "entity.h"
#include "fletchstestblock.h"
#include "fletchersplayer.h"
#include "box2d/box2d.h"
#include "elementtype.h"
#include "renderer.h"

//Library
#include <string>
#include <fstream>
#include <map>


//Declare
LevelParser* LevelParser::sm_pInstance = 0;

LevelParser::LevelParser()
	: m_pLevelData(new std::map<string, std::map<int, string>>())
	, m_tileSize(256.0f)
{

}

LevelParser::~LevelParser()
{
	delete m_pLevelData;
	m_pLevelData = nullptr;
}

LevelParser&
LevelParser::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new LevelParser();
	}

	return (*sm_pInstance);
}

void
LevelParser::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = nullptr;
}

bool
LevelParser::LoadLevelFile(const string& filename)
{
	ifstream fileData;

	fileData.open(filename);
	if (!fileData.is_open())
	{
		LogManager::GetInstance().Log("Level Parser Init Failed");
		return false;
	}

	string line;
	string level;
	int intLine = 0;
	while (std::getline(fileData, line))
	{
		line = Trim(line);

		//Ignore Empty Lines
		if (line.empty() || line[0] == ';')
		{
			continue;
		}

		if (line.front() == '[' && line.back() == ']')
		{
			level = Trim(line);
			intLine = 0;
		}
		else
		{
			(*m_pLevelData)[level][intLine] = line;
		}

		intLine++;
	}

	return true;
}

void
LevelParser::PrintMapValues()
{
	for (const auto& section : *m_pLevelData)
	{
		string logString = "[" + section.first + "]";
		LogManager::GetInstance().Log(logString.c_str());

		for (const auto& keyValue : section.second)
		{
			string logString = to_string(keyValue.first) + ". " + keyValue.second;
			LogManager::GetInstance().Log(logString.c_str());
		}
	}
}

string
LevelParser::Trim(const string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r\f\v");
	size_t last = str.find_last_not_of(" \t\n\r\f\v");

	return (first == std::string::npos || last == std::string::npos)
		? "" : str.substr(first, last - first + 1);
}

std::vector<Entity*>
LevelParser::LoadLevel(const string& levelname, Renderer& renderer)
{
	if (m_pLevelData->empty())
	{
		LoadLevelFile("data\\testmapdata.ini");
	}

	std::vector<Entity*> tileMap;
	auto levelSection = m_pLevelData->find(levelname);

	for (const auto& iValue : levelSection->second)
	{
		float y = static_cast<float>(iValue.first) * m_tileSize;
		float x = static_cast<int>(renderer.GetWidth() / 2);

		//Generate Tilemap
		for (int i = 0; i < iValue.second.length(); i++)
		{
			Entity* tile;
			if (iValue.second[i] == '#')
			{
				tile = new FletchsTestBlock(x, y);
				tileMap.push_back(tile);
			}

			if (iValue.second[i] == 'i')
			{
				tile = new FletchsTestBlock(x, y, ICE);
				tileMap.push_back(tile);
			}

			if (iValue.second[i] == 'e')
			{
				tile = new FletchsTestBlock(x, y, EARTH);
				tileMap.push_back(tile);
			}

			if (iValue.second[i] == 'f')
			{
				tile = new FletchsTestBlock(x, y, FIRE);
				tileMap.push_back(tile);
			}

			if (iValue.second[i] == 't')
			{
				tile = new FletchsTestBlock(x, y, TRAMP);
				tileMap.push_back(tile);
			}

			if (iValue.second[i] == 'p')
			{
				tile = new FletchersPlayer(x, y);
				tile->SetElementType(PLAYER);
				tileMap.push_back(tile);
			}
			x += m_tileSize;
		}
	}

	return tileMap;
}

void
LevelParser::SetTileSize(float size)
{
	m_tileSize = size;
}

std::map<string, std::map<int, string>>*
LevelParser::GetLevelData()
{
	return m_pLevelData;
}