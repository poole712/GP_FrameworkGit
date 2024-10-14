#pragma once
#ifndef _LEVELMANAGER_H

#include "scene.h"

#include <vector>
#include <map>
#include <string>

class Renderer;
class InputSystem;
class Level;
class SoundSystem;
class Entity;

using namespace std;

class LevelManager : public Scene
{
	//Member Methods
public:
	LevelManager();
	virtual ~LevelManager();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Process(float deltaTime, InputSystem& inputSystem, Game& game) { Process(deltaTime, inputSystem); };
	void LoadLevel(const string& level);
	void ResetLevel();
	void UnloadLevel();
	void Draw(Renderer& renderer);
	void DebugDraw();
	void NextLevel();
	void InitialiseSounds();

protected:

private:
	LevelManager(const LevelManager& levelmanager);
	LevelManager& operator=(const LevelManager& levelmanager);

	//MemberData
public:

protected:
	std::map<string, std::map<int, string>>* m_pLevelData;
	Level* m_pActiveLevel;
	Renderer* m_pRenderer;
	SoundSystem* m_pSoundSystem;

	vector<Entity*> m_EntityList;

private:

};

#endif //_LEVELMANAGER_H