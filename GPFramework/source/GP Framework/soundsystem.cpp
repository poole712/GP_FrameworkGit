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
	if (m_pSoundSystem)
	{
		m_pSoundSystem->release();
	}
}

bool
SoundSystem::Initialise()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_pSoundSystem);
	m_pSoundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

	if (result != FMOD_OK)
	{
		LogManager::GetInstance().Log("Error setting up sound system (initialise)");
	}
	return true;
}

void
SoundSystem::PlaySound(const char* soundname)
{
	auto it = m_Sounds.find(soundname);

	if (it != m_Sounds.end())
	{
		FMOD::Sound* sound = it->second;
		FMOD::Channel* channel = nullptr;

		m_pSoundSystem->playSound(sound, nullptr, false, &channel);

		// Store the channel for volume control
		m_Channels[soundname] = channel;
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
	auto it = m_Channels.find(soundName);

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
