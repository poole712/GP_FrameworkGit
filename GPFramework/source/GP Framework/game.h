#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
//Forward Declarations
class Renderer;
class Sprite;
class Scene;
class InputSystem;

class Game {

public:
	static Game& GetInstance();
	static void DestroyInstance();
	bool Initialise();
	bool DoGameLoop();
	void ToggleDebugWindow();
	void Quit();
	void SwitchScene(int scene);
protected:
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void DebugDraw();
	void ProcessFrameCounting(float deltaTime);

private:
	Game();
	~Game();
	Game(const Game& game);
	Game& operator=(const Game& game);


	//Member data
public:

protected:
	static Game* sm_pInstance;
	InputSystem* m_pInputSystem;
	Renderer* m_pRenderer;
	bool m_bShowDebugWindow;
	std::vector<Scene*> m_scenes;
	int m_iCurrentScene;

	_int64 m_iLastTime;
	float m_fExecutionTime;
	float m_fElapsedSeconds;
	int m_iFrameCount;
	int m_iFPS;

#ifdef USE_LAG
	float m_fLag;
	int m_iUpdateCount;
#endif // USE_LAG

	bool m_bLooping;

private:

};


#endif // !_GAME_H
