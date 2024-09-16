#ifndef  _SCENEBBMAINMENU_H
#define _SCENEBBMAINMENU_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;
class UiHandler;

class SceneBBMainMenu : public Scene
{
public:
	SceneBBMainMenu();
	virtual ~SceneBBMainMenu();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, int& scene);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	bool IsMouseOverObject(int mouseX, int mouseY, const Sprite& object);
protected:

private:
	SceneBBMainMenu(const SceneBBMainMenu& sceneCheckerboards);
	SceneBBMainMenu& operator=(const SceneBBMainMenu& sceneCheckerboards);

public:

protected:
	Sprite* m_pTitleSprite;

	Sprite* m_pPlayButton;

};
#endif // ! _SCENECHECKERBOARDS_H
