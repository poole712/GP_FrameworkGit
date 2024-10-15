#include "soundsystem.h"
#include <string>
#include <fmod.hpp>
#include <fmod.h>
#include "logmanager.h"

SoundSystem::SoundSystem()
	: m_pSoundSystem(0)
{

}

SoundSystem::~SoundSystem()
{
	for (auto it = m_Channels.begin(); it != m_Channels.end();)
	{
		(*it).second->stop();
		(*it).second = nullptr;
		it++;
	}

	if (m_pSoundSystem)
	{
		m_pSoundSystem->release();
		m_pSoundSystem = nullptr;
	}
}

bool
SoundSystem::Initialise()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_pSoundSystem);
	if (result != FMOD_OK)
	{
		LogManager::GetInstance().Log("Error setting up sound system (initialise)");
	}

	result = m_pSoundSystem->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		LogManager::GetInstance().Log("Error setting up sound system (initialise)");
	}

	m_pBGMChannel = nullptr;

	return true;
}

void
SoundSystem::PlaySound(const char* soundname)
{
	auto it = m_Sounds.find(soundname);

	if (it != m_Sounds.end())
	{
		FMOD::Sound* sound = it->second;
		auto chnl = m_Channels.find(sound);

		m_pSoundSystem->playSound(sound, nullptr, false, &chnl->second);
	}
	else
	{
		LogManager::GetInstance().Log("Failed to find sound in map, might need creation first.");
	}
}

void
SoundSystem::CreateSound(const char* filename, const char* soundName)
{
	FMOD::Sound* newSound = nullptr;
	m_pSoundSystem->createSound(filename, FMOD_DEFAULT, nullptr, &newSound);

	FMOD::Channel* channel = nullptr;
	// Store the channel for volume control
	m_Channels[newSound] = channel;

	m_Sounds.insert({ soundName, newSound });
}

void
SoundSystem::Process(float deltaTime)
{
	m_pSoundSystem->update();
}

// New function to change the volume of a sound
void
SoundSystem::SetVolume(const char* soundName, float volume)
{
	auto snd = m_Sounds.find(soundName);
	auto it = m_Channels.find(snd->second);

	if (it != m_Channels.end())
	{
		FMOD::Channel* channel = it->second;
		channel->setVolume(volume);  // Set the volume
	}
	else
	{
		LogManager::GetInstance().Log("Failed to find channel for the given sound.");
	}
}

void
SoundSystem::PauseSound(const char* soundName, bool pause)
{
	auto snd = m_Sounds.find(soundName);
	auto it = m_Channels.find(snd->second);

	if (it != m_Channels.end())
	{
		FMOD::Channel* channel = it->second;
		channel->setPaused(pause);  // Pause or resume the sound
	}
	else
	{
		LogManager::GetInstance().Log("Failed to find channel for the given sound.");
	}
}

void
SoundSystem::StopAllSound()
{
	for (auto it = m_Channels.begin(); it != m_Channels.end(); it++)
	{
		(*it).second->stop();
	}
}

void
SoundSystem::CreateBGM(const char* filename, const char* soundName)
{
	FMOD::Sound* newSound = nullptr;
	m_pSoundSystem->createSound(filename, FMOD_DEFAULT, nullptr, &newSound);

	m_bgm.insert({ soundName, newSound });
}

void
SoundSystem::PlayBGM(const char* bgmname)
{
	auto it = m_bgm.find(bgmname);
	bool isPlaying = false;

	FMOD_RESULT result;
	result = m_pBGMChannel->isPlaying(&isPlaying);
	if (isPlaying) { return; }

	if (it != m_bgm.end())
	{
		FMOD::Sound* sound = it->second;
	
		m_pSoundSystem->playSound(sound, nullptr, false, &m_pBGMChannel);
	}
	else
	{
		LogManager::GetInstance().Log("Failed to find sound in map, might need creation first.");
	}
}

void 
SoundSystem::StopBGM()
{
	m_pBGMChannel->stop();
}