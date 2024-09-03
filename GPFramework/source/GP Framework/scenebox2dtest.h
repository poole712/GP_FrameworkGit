#ifndef _SCENEBOX2DTEST_H
#define _SCENEBOX2DTEST_H

class b2World;
class Crate;
class Sprite;
class b2PolygonShape;
class b2Color;


#include "scene.h" 


class SceneBox2DTest : public Scene
{
	//Member methods
public:
	SceneBox2DTest();
	virtual ~SceneBox2DTest();
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual bool Initialise(Renderer& renderer);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();


protected:

private:
	SceneBox2DTest(const SceneBox2DTest& sceneBox2D);
	SceneBox2DTest& operator=(const SceneBox2DTest& sceneBox2D);

	//Member data:
public:

protected:
	b2Color* m_pColor;
	Sprite* m_pGroundSprite;
	b2World* m_pWorld;
	Crate* m_pCrate;
	b2PolygonShape* m_pGround;


private:
};


#endif // !_SCENEBOX2DTEST_H

