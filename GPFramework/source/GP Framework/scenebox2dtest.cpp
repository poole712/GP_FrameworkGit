#include "scenebox2dtest.h"

#include "box2d/box2d.h"
#include "crate.h"
#include "b2debugdraw.h"
#include "logmanager.h"
#include "sprite.h"
#include "renderer.h"

//DebugDraw debugDraw;

SceneBox2DTest::SceneBox2DTest()
{

}

SceneBox2DTest::~SceneBox2DTest()
{
	delete m_pWorld;
	m_pWorld = 0;
}

bool
SceneBox2DTest::Initialise(Renderer& renderer)
{
	

	b2Vec2 gravity;
	gravity.Set(0.0f, 100.0f);

	m_pWorld = new b2World(gravity);

	b2BodyDef ground;
	ground.position.Set(640.0f, 360.0f);

	b2Body* body = m_pWorld->CreateBody(&ground);

	m_pGround = new b2PolygonShape();
	m_pGround->SetAsBox(5.0f, 1.0f);


	body->CreateFixture(m_pGround, 0.0f);

	m_pCrate = new Crate();
	
	m_pCrate->Initialise(m_pWorld, renderer);
	
	m_pGroundSprite = renderer.CreateSprite("sprites\\board8x1.png");
	m_pGroundSprite->SetX(640.0f);
	m_pGroundSprite->SetY(375.0f);
	m_pGroundSprite->SetScale(0.1f);



	//debugDraw.SetFlags(b2Draw::e_shapeBit); // Set what to draw (shapes, joints, etc.)
	//m_pWorld->SetDebugDraw(&debugDraw);


	
	return true;
}

void SceneBox2DTest::Draw(Renderer& renderer)
{
	// Draw the crate as well
	m_pGroundSprite->Draw(renderer);
	m_pCrate->Draw(renderer);

}


void 
SceneBox2DTest::Process(float deltaTime, InputSystem& inputSystem)
{
	
	m_pWorld->Step(deltaTime, 6, 2);
	m_pGroundSprite->Process(deltaTime);
	


}

void
SceneBox2DTest::DebugDraw()
{
	m_pWorld->DebugDraw();

}