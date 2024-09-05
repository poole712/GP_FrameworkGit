#ifndef _CRATE_H
#define _CRATE_H

#include "box2d/box2d.h"

class Renderer;
class Sprite;

class Crate
{
public:

	Crate();
	~Crate();

	bool Initialise(b2World* b2world, Renderer& renderer);
	void Draw(Renderer& renderer);

protected:

private:

public:

protected:
	b2Body* m_pBody;
	b2Fixture* m_pFixture;
	b2PolygonShape* m_pShape;
	Sprite* m_pSprite;
	b2Color* debugColor;

};


#endif // !_CRATE_H
