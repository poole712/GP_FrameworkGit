#pragma once
#ifndef _LOGMANAGER_H_
#define _LOGMANAGER_H_

class LogManager {
	
	//Member Methods:
public:
	static LogManager& GetInstance();
	static void DestroyInstance();
	void Log(const char* pcMessage);

protected:

private:
	LogManager();
	~LogManager();
	LogManager(const LogManager& logManager);
	LogManager& operator=(const LogManager& logManager);

	//Member data:
public:

protected:
	static LogManager* sm_pInstance;

private:

};
#endif // !_LOGMANAGER_H_
