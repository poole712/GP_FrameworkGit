#include "fletchstestblock.h"

#include "sprite.h"
#include "box2d/box2d.h"
#include "renderer.h"

FletchsTestBlock::FletchsTestBlock(float x, float y)
{
	m_vStartPos = b2Vec2(x, y);
}

FletchsTestBlock::~FletchsTestBlock()
{

	delete m_pSprite;
	m_pSprite = 0;

}

bool
FletchsTestBlock::Initialise(b2World* world, Renderer& renderer)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;

	bodyDef.position.Set(m_vStartPos.x, m_vStartPos.y);
	m_pBody = world->CreateBody(&bodyDef);
	m_pBody->SetGravityScale(0.0f);

	b2PolygonShape polyShape;
	polyShape.SetAsBox(60.0f, 60.0f);
	m_pShape = &polyShape;

	b2FixtureDef fixDef;
	fixDef.shape = &polyShape;
	fixDef.density = 0.1f;
	fixDef.friction = 0.0f;
	fixDef.restitution = 0.0f;

	m_vVel = b2Vec2(-30.0f, 0.0f);
	m_pBody->SetLinearVelocity(m_vVel);
	m_pBody->SetLinearDamping(0.5f);


	m_pFixture = m_pBody->CreateFixture(&fixDef);
	m_pBody->SetFixedRotation(true);

	m_pSprite = renderer.CreateSprite("sprites\\FletchsTestPlayer.png");
	m_pSprite->SetScale(2.0f);

	return true;
}

void
FletchsTestBlock::Draw(Renderer& renderer)
{
	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);

	m_pSprite->Draw(renderer);
}


bool FletchsTestBlock::Initialise(Renderer& renderer)
{
	return false;
}

void
FletchsTestBlock::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);
	m_pSprite->SetAngle(m_pBody->GetAngle());


	
	m_position.x = m_pBody->GetPosition().x;
	m_position.y = m_pBody->GetPosition().y;
}
