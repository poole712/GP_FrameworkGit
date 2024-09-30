#ifndef _ENEMY_
#define _ENEMY_

#include "animatedentity.h"
#include "vector"

class Renderer;
class SoundSystem;


class Enemy : public AnimatedEntity
{
public:
	Enemy();
	virtual ~Enemy();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void Attack();
	virtual void StartAttacking();
	virtual void Die();

protected:
	void FireDelay(int milliseconds);


private:
	Enemy(const Enemy& blockBloke);
	Enemy& operator=(const Enemy& blockBloke);

public:

protected:
	char* m_cSpriteFileName;

	float m_fTimeToFirstFire;
	float m_fFirstFireDelay;

	float m_fHealth;

	float m_fTimeSinceLastFire;
	float m_fFireCooldown;
	bool m_bIsFiring;

};

#endif // !_SHIELD_H
 