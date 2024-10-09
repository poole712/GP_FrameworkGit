#ifndef  _FLETCHERSSCENE_H
#define _FLETCHERSSCENE_H

#include "scene.h"
#include "elementtype.h"

#include <vector>

class Renderer;
class Sprite;
class Game;
class InputSystem;
class UiHandler;
class FletchersPlayer;
class FletchsTestBlock;
class SoundSystem;
class b2World;
class Hud;

class FletchersScene : public Scene
{
public:
	FletchersScene();
	virtual ~FletchersScene();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

	void ToggleBlocks(ElementType type);

protected:

private:
	FletchersScene(const FletchersScene& sceneCheckerboards);
	FletchersScene& operator=(const FletchersScene& sceneCheckerboards);

public:

protected:
	FletchersPlayer* m_pPlayer;
	Hud* m_pHud;

	std::vector<FletchsTestBlock*> m_pTestBlocks;
	FletchsTestBlock* m_pSingleBlock;

	SoundSystem* m_pSoundSystem;
	b2World* m_pWorld;


};
#endif // ! _SCENECHECKERBOARDS_H
