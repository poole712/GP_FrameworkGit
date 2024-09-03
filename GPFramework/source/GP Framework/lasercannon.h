#ifndef _LASERCANNON_H
#define _LASERCANNON_H

#include "entity.h"
#include "laserbullet.h"
#include "vector"

class Renderer;
class Sprite;
class SoundSystem;

class LaserCannon : public Entity
{
public:
	LaserCannon();
	~LaserCannon();
	virtual bool Initialise(Renderer& renderer) override;
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;
	virtual void Draw(Renderer& renderer) override;
	void ShootBullet(SoundSystem &soundSystem);
	void Move(float x);
	LaserBullet* GetCurrentBullet();

protected:
	void FireDelay(int milliseconds);

private:
	LaserCannon(const LaserCannon& cannon);
	LaserCannon& operator=(const LaserCannon& cannon);

public:

protected:
	std::vector<LaserBullet*> m_pBullets;
	int m_iBulletIndex;
	float m_fTimeSinceLastFire;
	float m_fFireCooldown;
	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;
	bool m_bCanFire;
	LaserBullet* m_pCurrentBullet;

	
};

#endif // !_LASERCANNON_H
