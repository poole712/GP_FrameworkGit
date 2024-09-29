//This
#include "levelparser.h"

//Local
#include "logmanager.h"

//Library
#include <string>
#include <fstream>
#include <map>


//Declare
LevelParser* LevelParser::sm_pInstance = 0;

LevelParser::LevelParser()
	: m_pLevelData(new std::map<string, std::map<int, string>>())
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