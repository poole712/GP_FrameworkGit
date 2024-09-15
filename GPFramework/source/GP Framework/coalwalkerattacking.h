#ifndef _COALWALKERATTACKING_
#define _COALWALKERATTACKING_

#include "vector"
#include "enemy.h"

class SoundSystem;
class Renderer;
class Enemy;
class AnimatedEntity;

class CoalWalkerAttacking : public Enemy
{
public:
	CoalWalkerAttacking(bool goingLeft);
	virtual ~CoalWalkerAttacking();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void Die();

	void Shoot();

protected:

private:
	CoalWalkerAttacking(const CoalWalkerAttacking& blockBloke);
	CoalWalkerAttacking& operator=(const CoalWalkerAttacking& blockBloke);

public:

protected:
	bool m_bGoingLeft;
	

};

#endif // !_SHIELD_H
