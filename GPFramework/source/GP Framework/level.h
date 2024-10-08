#pragma once
#ifndef _LEVEL_H

#include "scene.h"
#include "elementtype.h"
#include <vector>

class Entity;
class b2World;
class SoundSystem;
class Hud;

using namespace std;

class Level : public Scene {
	//Member Methods
public:
	Level();
	virtual ~Level();

	bool Initialise(Renderer& renderer) { return false; };
	bool Initialise(Renderer& renderer, vector<Entity*> entityList);
	void Process(float deltaTime, InputSystem& inputSystem, Game& game) { Process(deltaTime, inputSystem); };
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);
	void DebugDraw();

	void ToggleBlocks(ElementType type);

protected:

private:
	Level(const Level& level);
	Level& operator=(const Scene& scene);

	//Member Data
public:

protected:
	vector<Entity*> m_entityList;
	b2World* m_pWorld;
	SoundSystem* m_pSoundSystem;
	Hud* m_pHud;

private:

};

#endif // !_LEVEL_H
