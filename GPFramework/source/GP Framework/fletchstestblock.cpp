#include "fletchstestblock.h"

#include "sprite.h"
#include "box2d/box2d.h"
#include "renderer.h"
#include "elementtype.h"

FletchsTestBlock::FletchsTestBlock(float x, float y, ElementType type)
{
	m_vStartPos = b2Vec2(x, y);
	m_elementType = type;
}

FletchsTestBlock::FletchsTestBlock(float x, float y)
{
	m_vStartPos = b2Vec2(x, y);
	m_elementType = NONE;
}

FletchsTestBlock::~FletchsTestBlock()
{
		delete m_pSprite;
		m_pSprite = 0;
}

bool
FletchsTestBlock::Initialise(Renderer& renderer, b2World& world, Level& scene)
{
	return Initialise(renderer, world);
}

bool
FletchsTestBlock::Initialise(Renderer& renderer, b2World& world)
{
	m_bAlive = true;

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;

	bodyDef.position.Set(m_vStartPos.x, m_vStartPos.y);
	m_pBody = world.CreateBody(&bodyDef);
	m_pBody->SetGravityScale(0.0f);

	m_pShape = new b2PolygonShape();
	m_pShape->SetAsBox(60.0f, 60.0f);

	b2FixtureDef fixDef;
	fixDef.shape = m_pShape;
	fixDef.density = 0.1f;
	fixDef.friction = 0.0f;
	fixDef.restitution = 0.0f;

	m_vVel = b2Vec2(-75.0f, 0.0f);
	m_pBody->SetLinearVelocity(m_vVel);
	m_pBody->SetLinearDamping(0.5f);


	m_pFixture = m_pBody->CreateFixture(&fixDef);
	m_pBody->SetFixedRotation(true);

	switch (m_elementType)
	{
	case FIRE:
		m_pSprite = renderer.CreateSprite("sprites\\fireblock.png");
		break;
	case EARTH:
		m_pSprite = renderer.CreateSprite("sprites\\earthblock.png");
		break;
	case ICE:
		m_pSprite = renderer.CreateSprite("sprites\\iceblock.png");
		break;
	case TRAMP:
		m_pSprite = renderer.CreateSprite("sprites\\trampblock.png");
		break;
	case FLAG:
		m_pSprite = renderer.CreateSprite("sprites\\temptramp.png");
		m_pSprite->SetRedTint(0);
		m_pSprite->SetBlueTint(0);
		break;
	default:
		m_pSprite = renderer.CreateSprite("sprites\\defaultblock.png");
		break;
	}

	m_pSprite->SetScale(2.0f);

	Toggle(NONE);

	return true;
}

void
FletchsTestBlock::Draw(Renderer& renderer)
{
	m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pSprite->SetY(m_pBody->GetPosition().y);

	m_pSprite->Draw(renderer);
}

void
FletchsTestBlock::Toggle(ElementType type)
{
	b2Filter filter;
	m_bToggledOn = false;

	if (m_elementType == type || m_elementType == NONE)
	{
		filter.maskBits = 0xFFFF;
		m_bToggledOn = true;
		m_pFixture->SetFilterData(filter);
		m_pSprite->SetAlpha(1.0f);
	}
	else if (m_elementType != TRAMP)
	{
		filter.maskBits = 0x0000;
		m_pFixture->SetFilterData(filter);
		m_pSprite->SetAlpha(0.5f);
	}

	if (m_elementType != PLAYER && m_elementType == TRAMP)
	{
		filter.maskBits = 0x0000;
		m_pFixture->SetFilterData(filter);
	}

	if (m_elementType != PLAYER && m_elementType == FLAG)
	{
		filter.maskBits = 0x0000;
		m_pFixture->SetFilterData(filter);
	}
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
