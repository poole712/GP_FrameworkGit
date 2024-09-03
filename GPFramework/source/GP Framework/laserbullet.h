#ifndef _LASERBULLET_H
#define _LASERBULLET_H

#include "entity.h"

class Renderer;
class LaserCannon;
class Sprite;

class LaserBullet : public Entity
{
public:
	LaserBullet();
	~LaserBullet();
	virtual bool Initialise(Renderer& renderer) override;
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;
	virtual void Draw(Renderer& renderer) override;
	void Setup(LaserCannon& player);

protected:

private:
	LaserBullet(const LaserBullet& cannon);
	LaserBullet& operator=(const LaserBullet& cannon);

public:


protected:

private:
};

#endif // !_LASERBULLET_H
