//This include
#include "logmanager.h"

//Library include
#include <Windows.h>

//Static members:
LogManager* LogManager::sm_pInstance = 0;

LogManager&
LogManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new LogManager();
	}
	return (*sm_pInstance);
}

void
LogManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

LogManager::LogManager()
{

}

LogManager::~LogManager()
{

}

void
LogManager::Log(const char* pcMessage)
{
	OutputDebugStringA(pcMessage);
	OutputDebugStringA("\n");
}

