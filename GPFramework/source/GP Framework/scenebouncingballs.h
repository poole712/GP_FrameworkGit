#ifndef  _SCENEBOUNCINGBALLS_H
#define _SCENEBOUNCINGBALLS_H

#include "scene.h"

class Renderer;
class Ball;
class InputSystem;

class SceneBouncingBalls : public Scene
{
public:
	SceneBouncingBalls();
	virtual ~SceneBouncingBalls();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:
	SceneBouncingBalls(const SceneBouncingBalls& sceneBounxingBalls);
	SceneBouncingBalls& operator=(const SceneBouncingBalls& sceneBouncingBalls);

public:

protected:
	int m_iShowCount;
	Ball* m_pBalls[100];

private:

};

#endif // ! _SCENEBOUNCINGBALLS_H
