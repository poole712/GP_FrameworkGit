#ifndef _SHIELD_H
#define _SHIELD_H

#include "entity.h"
#include "vector"

class Renderer;
class Sprite;
class SoundSystem;
class Shield;
class b2Body;
class b2Fixture;
class b2World;

class Shield : public Entity
{
public:
	Shield();
	virtual ~Shield();

	virtual bool Initialise(Renderer& renderer) override;
	bool Initialise(Renderer& renderer, b2World* world);
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;
	virtual void Draw(Renderer& renderer) override;
	void ShieldRotate(float dir);

protected:
	void FireDelay(int milliseconds);
	void Move(float x);


private:
	Shield(const Shield& blockBloke);
	Shield& operator=(const Shield& blockBloke);

public:

protected:
	b2Body* m_pBody;
	b2Fixture* m_pFixture;
};

#endif // !_SHIELD_H
