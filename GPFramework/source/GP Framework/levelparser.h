#pragma once
#ifndef _LEVELPARSER_H
#define _LEVELPARSER_H

#include <string>
#include <map>

class map;

using namespace std;

class LevelParser
{
	//Member Methods
public:
	static LevelParser& GetInstance();
	static void DestroyInstance();

	bool LoadLevelFile(const string& filename);
	void PrintMapValues();

private:
	LevelParser();
	~LevelParser();
	LevelParser(const LevelParser& levelParser);
	LevelParser& operator=(const LevelParser& levelParser);

protected:

private:
	string Trim(const string& str);

	//Member Data
public:

protected:
	static LevelParser* sm_pInstance;
	std::map<string, std::map<int, string>>* m_pLevelData;

private:
};

#endif // !_LEVELPARSER_H
