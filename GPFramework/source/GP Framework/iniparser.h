#pragma once
#ifndef __INIPARSER_H
#define __INIPARSER_H

#include <string>
#include <map>

class map;

using namespace std;

class IniParser
{
	//Member Methods
public:
	static IniParser& GetInstance();
	static void DestroyInstance();

	bool LoadIniFile(const string& filename);
	string GetValueAsString(const string& iniSection, const string& key);
	int GetValueAsInt(const string& iniSection, const string& key);
	float GetValueAsFloat(const string& iniSection, const string& key);
	bool GetValueAsBoolean(const string& iniSection, const string& key);
	void PrintMapValues();

private:
	IniParser();
	~IniParser();
	IniParser(const IniParser& iniParser);
	IniParser& operator=(const IniParser& iniParser);

protected:

private:
	string Trim(const string& str);

	//Member Data
public:

protected:
	static IniParser* m_pInstance;
	std::map<string, std::map<string, string>>* m_pIniData;

private:
};

#endif // !__INIPARSER_H
