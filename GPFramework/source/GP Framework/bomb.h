#ifndef _BOMB_H
#define _BOMB_H

#include "entity.h"
#include "vector"
#include "animatedentity.h"

class Renderer;
class Sprite;

class Bomb : public AnimatedEntity
{
public:
	Bomb();
	~Bomb();

	virtual bool Initialise(Renderer& renderer) override;
	virtual void Process(float deltaTime) override;
	virtual void Draw(Renderer& renderer) override;

	void Deflect();
	void SetHitPlayer();
	float m_fRotationSpeed;

protected:
	void FireDelay(int milliseconds);
	void Move(float x);
	void Jump();


private:
	Bomb(const Bomb& blockBloke);
	Bomb& operator=(const Bomb& blockBloke);

public:

protected:
	bool m_bHitPlayer;

	Vector2 m_vFireballPos;
};

#endif // !_BLOCKBLOKE
