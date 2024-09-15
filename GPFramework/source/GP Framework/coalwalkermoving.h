#ifndef _COALWALKERMOVING_
#define _COALWALKERMOVING_

#include "vector"
#include "enemy.h"

class SoundSystem;
class Renderer;
class Enemy;
class AnimatedEntity;

class CoalWalkerMoving : public Enemy
{
public:
	CoalWalkerMoving(bool goingLeft);
	virtual ~CoalWalkerMoving();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void Die();

	void ResetPosition();

protected:

private:
	CoalWalkerMoving(const CoalWalkerMoving& blockBloke);
	CoalWalkerMoving& operator=(const CoalWalkerMoving& blockBloke);

public:

protected:
	bool m_bGoingLeft;


};

#endif // !_SHIELD_H
