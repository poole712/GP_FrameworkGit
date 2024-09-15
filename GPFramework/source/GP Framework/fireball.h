#ifndef _FIREBALL_H
#define _FIREBALL_H

#include "entity.h"
#include "vector"
#include "animatedentity.h"

class Renderer;
class Sprite;
class SoundSystem;
class Explosion;

class Fireball : public AnimatedEntity
{
public:
	Fireball(bool goingLeft);
	~Fireball();

	virtual bool Initialise(Renderer& renderer) override;
	virtual void Process(float deltaTime) override;
	virtual void Draw(Renderer& renderer) override;

	void SetPositionWithResetPos(float x, float y);
	void Deflect();
	float m_fRotationSpeed;

protected:
	void FireDelay(int milliseconds);
	void Move(float x);
	void Jump();


private:
	Fireball(const Fireball& blockBloke);
	Fireball& operator=(const Fireball& blockBloke);

public:

protected:
	bool m_bGoingRight;
	bool m_bFlying;
	bool m_bHitBack;

	Vector2 m_vFireballPos;
};

#endif // !_BLOCKBLOKE
