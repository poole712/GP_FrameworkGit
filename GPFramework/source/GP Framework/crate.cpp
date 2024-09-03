#include "crate.h"

#include "sprite.h"
#include "box2d/box2d.h"
#include "renderer.h"

Crate::Crate()
{

}

Crate::~Crate()
{

}

bool
Crate::Initialise(b2World* world, Renderer& renderer)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(640.0f, 100.0f);
	m_pBody = world->CreateBody(&bodyDef);

	b2PolygonShape polyShape;
	polyShape.SetAsBox(2.5f, 1.0f);

	b2FixtureDef fixDef;
	fixDef.shape = &polyShape;
	fixDef.density = 1.0f;
	fixDef.friction = 0.3f;

	m_pFixture = m_pBody->CreateFixture(&fixDef);


	m_pSprite = renderer.CreateSprite("sprites\\ball.png");
	m_pSprite->SetScale(0.1f);

	return true;
}

void
Crate::Draw(Renderer& renderer)
{
	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);

	
	m_pSprite->Draw(renderer);
}
