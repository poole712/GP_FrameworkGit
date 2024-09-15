#ifndef _WOLFRUNNER_
#define _WOLFRUNNER_

#include "vector"
#include "enemy.h"

class SoundSystem;
class Renderer;
class Enemy;
class AnimatedEntity;

class WolfRunner : public Enemy
{
public:
	WolfRunner(bool goingLeft);
	virtual ~WolfRunner();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void Die();

	void SetPositionWithResetPos(float x, float y);

protected:

private:
	WolfRunner(const WolfRunner& blockBloke);
	WolfRunner& operator=(const WolfRunner& blockBloke);

public:

protected:
	bool m_bGoingLeft;
	Vector2 m_vResetPos;

};

#endif // !_SHIELD_H
