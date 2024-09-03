#ifndef _INVADER_H
#define _INVADER_H

#include "entity.h"

class Renderer;
class LaserCannon;
class Sprite;

class Invader : public Entity
{
public:
	Invader();
	~Invader();
	virtual bool Initialise(Renderer& renderer) override;
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;
	virtual void Draw(Renderer& renderer) override;
	void SetPlayerRef(LaserCannon& lasercannon);
	void SetPosition(float x, float y);

protected:

private:
	Invader(const Invader& cannon);
	Invader& operator=(const Invader& cannon);

public:

protected:
	LaserCannon* m_pPlayer;

private:
};

#endif
