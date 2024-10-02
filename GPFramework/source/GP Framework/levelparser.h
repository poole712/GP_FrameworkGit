#pragma once
#ifndef _LEVELPARSER_H
#define _LEVELPARSER_H

#include <string>
#include <map>
#include <vector>

class map;
class Entity;

using namespace std;

class LevelParser
{
	//Member Methods
public:
	static LevelParser& GetInstance();
	static void DestroyInstance();

	bool LoadLevelFile(const string& filename);
	std::vector<Entity*> LoadLevel(const string& levelname);
	void PrintMapValues();
	void SetTileSize(float size);

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

	float m_tileSize;

private:
};

#endif // !_LEVELPARSER_H
