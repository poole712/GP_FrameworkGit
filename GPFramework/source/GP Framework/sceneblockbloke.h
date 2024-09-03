#ifndef  _SCENEBLOCKBLOKE_H
#define _SCENEBLOCKBLOKE_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;

class SceneBlockBloke : public Scene
{
public:
	SceneBlockBloke();
	virtual ~SceneBlockBloke();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:
	SceneBlockBloke(const SceneBlockBloke& sceneBlockBloke);
	SceneBlockBloke& operator=(const SceneBlockBloke& sceneBlockBloke);

public:

protected:
	Sprite* m_pPlayer;


	float m_angle;
	float m_rotationSpeed;
};
#endif // ! _SCENECHECKERBOARDS_H
