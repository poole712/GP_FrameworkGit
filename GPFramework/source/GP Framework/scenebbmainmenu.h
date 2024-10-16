#pragma once
#ifndef  _SCENEBBMAINMENU_H
#define _SCENEBBMAINMENU_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;
class UiHandler;
class Game;
class SoundSystem;
class Background;

class SceneBBMainMenu : public Scene
{
public:
	SceneBBMainMenu();
	virtual ~SceneBBMainMenu();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	bool IsMouseOverObject(float mouseX, float mouseY, const Sprite& object);

protected:

private:
	SceneBBMainMenu(const SceneBBMainMenu& sceneCheckerboards);
	SceneBBMainMenu& operator=(const SceneBBMainMenu& sceneCheckerboards);

public:

protected:
	Sprite* m_pTitleSprite;
	Sprite* m_pPlayButton;
	Sprite* m_pQuitButton;

	Background* m_bBackground;

	InputSystem* m_iInputSystem;

	SoundSystem* m_pSoundSystem;
};
#endif
