#ifndef _BLOCKBLOKE_H
#define _BLOCKBLOKE_H

#include "entity.h"
#include "vector"

class Renderer;
class Sprite;
class SoundSystem;
class Shield;

class BlockBloke : public Entity
{
public:
	BlockBloke();
	~BlockBloke();

	virtual bool Initialise(Renderer& renderer) override;
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;
	virtual void Draw(Renderer& renderer) override;
	void ShootBullet(SoundSystem& soundSystem);

protected:
	void FireDelay(int milliseconds);
	void Move(float x);


private:
	BlockBloke(const BlockBloke& blockBloke);
	BlockBloke& operator=(const BlockBloke& blockBloke);

public:

protected:
	Sprite* m_pSprite;
	Shield* m_pShield;

	int m_iHealth;
	int m_iAmmo;

	bool m_bCanFire;

	float m_fTimeSinceLastFire;
	float m_fFireCooldown;

	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;

};

#endif // !_BLOCKBLOKE
