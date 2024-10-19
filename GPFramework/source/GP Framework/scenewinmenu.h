#ifndef  _SCENEWINMENU_H
#define _SCENEWINMENU_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;
class UiHandler;
class Game;
class Background;

class SceneWinMenu : public Scene
{
public:
	SceneWinMenu();
	virtual ~SceneWinMenu();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	bool IsMouseOverObject(float mouseX, float mouseY, const Sprite& object);
protected:

private:
	SceneWinMenu(const SceneWinMenu& sceneWinMenu);
	SceneWinMenu& operator=(const SceneWinMenu& sceneWinMenu);

public:

protected:
	Sprite* m_pTitleSprite;

	Sprite* m_pQuitToMenuButton;

	Background* m_bBackground;

};
#endif // ! _SCENECHECKERBOARDS_H
