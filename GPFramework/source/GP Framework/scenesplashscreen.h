#pragma once
#ifndef __SCENE_SPLASHSCREEN_H
#define __SCENE_SPLASHSCREEN_H

#include "scene.h"

class Sprite;

enum Logo
{
	AUT,
	F_MOD,
	DONE
};

class SceneSplashscreen : public Scene {
	//Member Methods
public:
	SceneSplashscreen();
	virtual ~SceneSplashscreen();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	void Draw(Renderer& renderer);

	void DebugDraw();

protected:

private:

	//Member Data
public:

protected:

private:
	Sprite* m_pAutLogo;
	Sprite* m_pFmodLogo;

	Logo m_currentLogo;
	float m_fTotalTime;
	float m_fTime;
	float m_fFrameTime;
	float m_fTimeElapsed;
};

#endif // !__SCENE_SPLASHSCREEN_H
