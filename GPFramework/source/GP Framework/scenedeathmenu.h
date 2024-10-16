#ifndef  _SCENEDEATHMENU_H
#define _SCENEDEATHMENU_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;
class UiHandler;
class Game;
class Background;

class SceneDeathMenu : public Scene
{
public:
	SceneDeathMenu();
	virtual ~SceneDeathMenu();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	bool IsMouseOverObject(float mouseX, float mouseY, const Sprite& object);
protected:

private:
	SceneDeathMenu(const SceneDeathMenu& sceneCheckerboards);
	SceneDeathMenu& operator=(const SceneDeathMenu& sceneCheckerboards);

public:

protected:
	Sprite* m_pTitleSprite;

	Sprite* m_pRetryButton;
	Sprite* m_pQuitToMenuButton;

	Background* m_bBackground;

};
#endif // ! _SCENECHECKERBOARDS_H
