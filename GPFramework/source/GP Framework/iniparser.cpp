//Local
#include "iniparser.h"
#include "logmanager.h"

//Library
#include <string>
#include <fstream>
#include <map>


using namespace std;

IniParser* IniParser::m_pInstance = 0;

IniParser::IniParser()
	: m_pIniData(new std::map<string, std::map<string, string>>())
{

}

IniParser::~IniParser()
{
	delete m_pIniData;
	m_pIniData = 0;
}

IniParser&
IniParser::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new IniParser();
	}

	return (*m_pInstance);
}

void
IniParser::DestroyInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

bool
IniParser::LoadIniFile(const string& filename)
{
	ifstream fileData;
	std::map<string, std::map<string, string>> iniMap;

	fileData.open(filename);
	if (!fileData.is_open())
	{
		return false;
	}

	string line;
	string currentSection;
	while (std::getline(fileData, line))
	{
		line = Trim(line);

		//Ignore Empty Lines
		if (line.empty() || line[0] == ';' || line[0] == '#')
		{
			continue;
		}

		//Section Handler
		if (line.front() == '[' && line.back() == ']')
		{
			currentSection = line.substr(1, line.size() - 2);
		}
		else
		{
			size_t pos = line.find('=');
			if (pos != string::npos)
			{
				string key = Trim(line.substr(0, pos));
				string value = Trim(line.substr(pos + 1));
				(*m_pIniData)[currentSection][key] = value;
			}
		}
	}

	fileData.close();
	return true;
}

string
IniParser::Trim(const string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r\f\v");
	size_t last = str.find_last_not_of(" \t\n\r\f\v");

	return (first == std::string::npos || last == std::string::npos)
		? "" : str.substr(first, last - first + 1);
}


string
IniParser::GetValueAsString(const string& iniSection, const string& key)
{
	auto iteratorSection = m_pIniData->find(iniSection);
	if (iteratorSection != m_pIniData->end())
	{
		auto iteratorKey = iteratorSection->second.find(key);
		if (iteratorKey != iteratorSection->second.end())
		{
			return iteratorKey->second;
		}
	}
	return "";
}

void
IniParser::PrintMapValues()
{
	for (const auto& section : *m_pIniData)
	{
		string logString = "[" + section.first + "]";
		LogManager::GetInstance().Log(logString.c_str());

		for (const auto& keyValue : section.second)
		{
			string logString = keyValue.first + " = " + keyValue.second;
			LogManager::GetInstance().Log(logString.c_str());
		}
	}
}

int
IniParser::GetValueAsInt(const string& iniSection, const string& key)
{
	string data = GetValueAsString(iniSection, key);
	try
	{
		return std::stoi(data);
	}
	catch (const std::invalid_argument)
	{
		string logString = "Invalid argument for int conversion: " + data;
		LogManager::GetInstance().Log(logString.c_str());
		return 0;
	}
	catch (const std::out_of_range&)
	{
		string logString = "Out of range for int conversion: " + data;
		return 0;
	}
}

float
IniParser::GetValueAsFloat(const string& iniSection, const string& key)
{
	std::string data = GetValueAsString(iniSection, key);
	try
	{
		float value = std::stof(data);
		return value;
	}
	catch (const std::invalid_argument&)
	{
		string logString = "Invalid argument for float conversion: " + data;
		LogManager::GetInstance().Log(logString.c_str());
		return 0.0f;
	}
	catch (const std::out_of_range&)
	{
		string logString = "Out of range for float conversion: " + data;
		LogManager::GetInstance().Log(logString.c_str());
		return 0.0f;
	}
}

bool
IniParser::GetValueAsBoolean(const string& iniSection, const string& key)
{
	int data = GetValueAsInt(iniSection, key);

	if (data == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}