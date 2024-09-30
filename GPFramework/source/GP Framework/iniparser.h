#ifndef _INIPARSER_H_
#define _INIPARSER_H_

#include <string>
#include <map>

using std::string;

class IniParser
{
public:
	bool LoadIniFile(const string& filename);

	string GetValueAsString(const string& iniSection, const string& key);
	int GetValueAsInt(const string& iniSection, const string& key);
	float GetValueAsFloat(const string& iniSection, const string& key);
	bool GetValueAsBoolean(const string& iniSection, const string& key);

protected:

private:

public:

protected:
	std::map<std::string, std::string> m_dataMap;
private:

};

#endif // !_INIPARSER_H
