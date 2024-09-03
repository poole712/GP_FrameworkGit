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

protected:

private:
	SoundSystem(const SoundSystem& textureManager);
	SoundSystem& operator=(const SoundSystem& textureManager);

	//Member data:
public:

protected:
	FMOD::System* m_pSoundSystem;
	std::map<const char*, FMOD::Sound*> m_Sounds;

private:

};


#endif // !_SOUNDSYSTEM_H

