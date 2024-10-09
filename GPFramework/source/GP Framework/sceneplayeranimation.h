#ifndef  _SCENEPLAYERANIMATION_H
#define _SCENEPLAYERANIMATION_H

#include "scene.h"

class Renderer;
class Sprite;
class AnimatedSprite;
class InputSystem;
class Player;
class Game;

class ScenePlayerAnimation : public Scene
{
public:
	ScenePlayerAnimation();
	virtual ~ScenePlayerAnimation();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:
	ScenePlayerAnimation(const ScenePlayerAnimation& scenePlayerAnimation);
	ScenePlayerAnimation& operator=(const ScenePlayerAnimation& scenePlayerAnimation);

public:

protected:
	Player* m_pPlayer;
	Renderer* m_rRenderer;

};
#endif // ! _SCENECHECKERBOARDS_H
