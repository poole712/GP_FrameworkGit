#include "shield.h"

#include "logmanager.h"
#include "renderer.h"
#include "sprite.h"
#include "soundsystem.h"
#include "box2d/box2d.h"

#include <thread>
#include <chrono>


Shield::Shield()
{
}

Shield::~Shield()
{
	
	delete debugColor;
	debugColor = 0;

	delete m_pFixture;
	m_pFixture = 0;

	delete m_pShape;
	m_pShape = 0;
}

bool
Shield::Initialise(Renderer& renderer)
{
	return true;
}

bool
Shield::Initialise(Renderer& renderer, b2World* world)
{
	m_pSprite = renderer.CreateSprite("sprites\\shield.png");
	m_pSprite->SetScale(0.5f);
	m_fCurrentRotation = 180.0f;
	Rotate(180.0f);

	const int EDGE_LIMIT = m_pSprite->GetWidth();
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_position.x = SCREEN_WIDTH / 2.0f;
	m_position.y = (SCREEN_HEIGHT / 1.25f);


	//Physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(m_position.x, m_position.y - 60.0f);
	m_pBody = world->CreateBody(&bodyDef);
	m_pBody->SetGravityScale(0);
	

	b2PolygonShape polyShape;
	polyShape.SetAsBox(2.5f, 1.0f);

	b2FixtureDef fixDef;
	fixDef.shape = &polyShape;
	fixDef.density = 1.0f;
	fixDef.friction = 0.3f;

	m_pFixture = m_pBody->CreateFixture(&fixDef);
	m_pBody->SetAngularDamping(5.0f);
	m_pBody->GetFixtureList()->SetSensor(true);


	m_pBody->SetTransform(m_pBody->GetPosition(), 180);

	return true;
}

void
Shield::Process(float deltaTime, InputSystem& inputSystem)
{
	//m_pSprite->SetY(m_pBody->GetPosition().y + 50.0f);
	//m_pSprite->SetX(m_pBody->GetPosition().x);
	m_pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	m_pSprite->SetAngle(m_pBody->GetAngle());


}

void
Shield::Draw(Renderer& renderer)
{
	m_pSprite->Draw(renderer);
	
	debugColor = new b2Color;
	debugColor->Set(0, 1, 0);


	

}

float
Shield::GetShieldRot()
{
	return m_pBody->GetAngle();
}

void
Shield::ShieldRotate(float direction)
{
	m_fCurrentRotation = direction;
	m_pBody->ApplyAngularImpulse(direction, true);


}
