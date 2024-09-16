#ifndef  _SCENEBLOCKBLOKE_H
#define _SCENEBLOCKBLOKE_H

#include "scene.h"

class Renderer;
class Sprite;
class InputSystem;
class BlockBloke;
class b2World;
class Crate;
class Sprite;
class b2PolygonShape;
class EnemyGenerator;
class UiHandler;
class Explosion;
class SoundSystem;

class MyDebugDraw;

class SceneBlockBloke : public Scene
{
public:
	SceneBlockBloke();
	virtual ~SceneBlockBloke();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem, int& scene);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

	static MyDebugDraw* debugDraw;

protected:

private:
	SceneBlockBloke(const SceneBlockBloke& sceneBlockBloke);
	SceneBlockBloke& operator=(const SceneBlockBloke& sceneBlockBloke);

public:

protected:
	BlockBloke* m_pPlayer;
	EnemyGenerator* m_pEnemyGenerator;
	UiHandler* m_pUiHandler;

	SoundSystem* m_pSoundSystem;

	float m_angle;
	float m_rotationSpeed;

	//Physics:
	Sprite* m_pBackgroundSprite;
	b2World* m_pWorld;
	Crate* m_pCrate;
	b2PolygonShape* m_pGround;

};
#endif // ! _SCENECHECKERBOARDS_H
