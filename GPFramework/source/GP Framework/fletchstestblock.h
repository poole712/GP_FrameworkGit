#ifndef _FLETCHSTESTBLOCK_H
#define _FLETCHSTESTBLOCK_H

#include "box2d/box2d.h"
#include "entity.h"
#include "elementtype.h"

class Renderer;
class Sprite;
class b2Vec2;

class FletchsTestBlock : public Entity
{
public:

	FletchsTestBlock(float startX, float startY, ElementType type);
	~FletchsTestBlock();

	virtual bool Initialise(Renderer& renderer) override;
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;

	bool Initialise(b2World* b2world, Renderer& renderer);
	void Draw(Renderer& renderer);

	void Toggle(ElementType type);
	ElementType GetType();

protected:

private:
	FletchsTestBlock(const FletchsTestBlock& blockBloke);
	FletchsTestBlock& operator=(const FletchsTestBlock& blockBloke);

public:

protected:
	b2Body* m_pBody;
	b2Fixture* m_pFixture;
	b2PolygonShape* m_pShape;
	Sprite* m_pSprite;
	b2Vec2 m_vVel;
	b2Vec2 m_vStartPos;
	ElementType m_eType;

	// Inherited via Entity


};


#endif // !_CRATE_H
