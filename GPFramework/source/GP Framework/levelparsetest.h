#pragma once
#ifndef _LEVELPARSETEST_H

#include "scene.h"
#include <vector>
#include <string>

class Entity;
class b2World;

using namespace std;

class LevelParseTest : public Scene {
	//Member Methods
public:
	LevelParseTest();
	virtual ~LevelParseTest();

	bool Initialise(Renderer& renderer);
	virtual bool Initialise(Renderer& renderer, const string& levelname);
	void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	void Draw(Renderer& renderer);
	void DebugDraw();

protected:

private:

	//Member Data
public:

protected:
	std::vector<Entity*> m_entityList;
	b2World* m_pWorld;

private:

};

#endif // !_LEVELPARSETEST_H
