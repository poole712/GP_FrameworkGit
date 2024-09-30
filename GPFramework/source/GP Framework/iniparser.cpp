#include "iniparser.h"

#include "logmanager.h"

#include <fstream>
#include <string>

using std::string;


bool
IniParser::LoadIniFile(const string& filename)
{
	std::fstream file;
	string line;
	file.open(filename);
	if (file.is_open())
	{
		string currentSection;
		while (std::getline(file, line))
		{
			if (!line.empty())
			{
				if (line.front() == '[')
				{
					currentSection = line;
					currentSection.erase(0, 1);
					currentSection.erase(currentSection.find_last_of(']'));
				}
				else
				{
					int length = line.find_first_of('=');

					m_dataMap.insert({ currentSection + "|" + line.substr(0, length - 1), line.substr(length + 2, sizeof(line)) });
				}
				if (file.fail())
				{
					break;
				}
			}
			
		}
	}
	else
	{
		return false;
	}

	for (const auto& pair : m_dataMap)
	{
		string output = pair.first.c_str();
		output.append("\n");

		output.append(pair.second.c_str());
		output.append("\n");
		LogManager::GetInstance().Log(output.c_str());
	}
	LogManager::GetInstance().Log("Getting a value:");
	string key = "sectionName|itemName";
	auto it = m_dataMap.find(key);
	LogManager::GetInstance().Log(it->second.c_str());

	return true;
}
