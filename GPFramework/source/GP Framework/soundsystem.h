#ifndef _SOUNDSYSTEM_H

#include <map>
#include <string>
#include <fmod.hpp>


class SoundSystem
{
	//Member methods
public:
	SoundSystem();
	~SoundSystem();
	void Process(float deltaTime);
	bool Initialise();

	void CreateSound(const char* filename, const char* soundName);
	void PlaySound(const char* soundname);
	void SetVolume(const char* soundName, float volume);
	void PauseSound(const char* soundName, bool pause);
	void StopAllSound();
	void CreateBGM(const char* filename, const char* soundName);
	void PlayBGM(const char* bgmname);
	void StopBGM();

protected:

private:
	SoundSystem(const SoundSystem& textureManager);
	SoundSystem& operator=(const SoundSystem& textureManager);

	//Member data:
public:

protected:
	FMOD::System* m_pSoundSystem;
	std::map<const char*, FMOD::Sound*> m_Sounds;
	std::map<FMOD::Sound*, FMOD::Channel*> m_Channels;

	std::map<const char*, FMOD::Sound*> m_bgm;
	FMOD::Channel* m_pBGMChannel;
	
private:

};


#endif // !_SOUNDSYSTEM_H

