#ifndef  _SCENECHECKERBOARDS_H
#define _SCENECHECKERBOARDS_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;

class SceneCheckerboards : public Scene
{
public:
	SceneCheckerboards();
	virtual ~SceneCheckerboards();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:
	SceneCheckerboards(const SceneCheckerboards& sceneCheckerboards);
	SceneCheckerboards& operator=(const SceneCheckerboards& sceneCheckerboards);

public:

protected:
	Sprite* m_pCorners[4];
	Sprite* m_pCentre;

	float m_angle;
	float m_rotationSpeed;
};
#endif // ! _SCENECHECKERBOARDS_H
