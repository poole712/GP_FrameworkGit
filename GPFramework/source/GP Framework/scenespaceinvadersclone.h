#ifndef _SCENESPACERINVADERSCLONE_H
#define _SCENESPACEINVADERSCLONE_H

#include "scene.h"
#include "lasercannon.h"
#include "invader.h"

class ParticleEmitter;
class SoundSystem;

class SceneSpaceInvadersClone : public Scene
{
public:
	SceneSpaceInvadersClone();
	virtual ~SceneSpaceInvadersClone();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();

protected:

private:
	SceneSpaceInvadersClone(const SceneSpaceInvadersClone& sceneBounxingBalls);
	SceneSpaceInvadersClone& operator=(const SceneSpaceInvadersClone& sceneBouncingBalls);

public:

protected:
	int m_iShowCount;
	LaserCannon* m_pLaserCannon;
	ParticleEmitter* m_pParticleEmitter;
	std::vector<Invader*> m_pInvaders;
	SoundSystem* m_pSoundSystem;

private:
};

#endif // !_SCENESPACERINVADERSCLONE_H
