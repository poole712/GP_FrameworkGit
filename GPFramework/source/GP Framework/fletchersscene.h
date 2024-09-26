#ifndef  _FLETCHERSSCENE_H
#define _FLETCHERSSCENE_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;
class UiHandler;
class Entity;

class FletchersScene : public Scene
{
public:
	FletchersScene();
	virtual ~FletchersScene();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, int& scene);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:
	FletchersScene(const FletchersScene& sceneCheckerboards);
	FletchersScene& operator=(const FletchersScene& sceneCheckerboards);

public:

protected:
	Entity* m_pPlayer;

};
#endif // ! _SCENECHECKERBOARDS_H
