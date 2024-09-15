#ifndef _COALWALKER_
#define _COALWALKER_

#include "vector"
#include "enemy.h"

class SoundSystem;
class Renderer;
class Enemy;
class AnimatedEntity;
class CoalWalkerMoving;
class CoalWalkerAttacking;
class Fireball;
class BlockBloke;
class SoundSystem;

class CoalWalker  
{
public:
	CoalWalker(bool goingLeft);
	~CoalWalker();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, BlockBloke& player, SoundSystem& soundSystem);
	void Draw(Renderer& renderer);
	void Attack();
	void StartAttacking();
	void Die();

	bool GetAliveState();
	void SetAlive(bool alive);
protected:
	void FireDelay(int milliseconds);


private:
	CoalWalker(const CoalWalker& blockBloke);
	CoalWalker& operator=(const CoalWalker& blockBloke);

public:

protected:
	bool m_bGoingLeft;
	bool m_bIsFiring;
	bool m_bIsAlive;

	Vector2 m_v2StartPos;

	int m_iCurrentFBIndex;

	CoalWalkerMoving* m_pMovingCoalWalker;
	CoalWalkerAttacking* m_pAttackingCoalWalker;

	std::vector<Fireball*> m_pFireballs;

	float m_fTimeSinceLastFire;
	float m_fTimeToFirstFire;

	float m_fFireCooldown;
	float m_fFirstFireDelay;
};

#endif // !_SHIELD_H
