#include "sceneblockbloke.h"

#include "renderer.h"
#include "sprite.h"
#include "imgui/imgui.h"
#include "b2debugdraw.h"
#include "blockbloke.h"
#include "box2d/box2d.h"
#include "crate.h"


#include <cassert>

//DebugDraw debugDraw;


SceneBlockBloke::SceneBlockBloke()
	:  m_angle(0.0f), m_rotationSpeed(0.0f)
{

}

SceneBlockBloke::~SceneBlockBloke()
{
	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_pWorld;
	m_pWorld = 0;

	m_pWorld->~b2World();
}

bool
SceneBlockBloke::Initialise(Renderer& renderer)
{
	

	//Physics:
	b2Vec2 gravity;
	gravity.Set(0.0f, 100.0f);
	m_pWorld = new b2World(gravity);

	b2BodyDef ground;
	ground.position.Set(640.0f, 580.0f);
	b2Body* body = m_pWorld->CreateBody(&ground);

	m_pGround = new b2PolygonShape();
	m_pGround->SetAsBox(5.0f, 1.0f);
	body->CreateFixture(m_pGround, 0.0f);

	m_pCrate = new Crate();
	m_pCrate->Initialise(m_pWorld, renderer);

	m_pGroundSprite = renderer.CreateSprite("sprites\\board8x1.png");
	m_pGroundSprite->SetX(640.0f);
	m_pGroundSprite->SetY(600.0f);
	m_pGroundSprite->SetScale(0.1f);

	m_pPlayer = new BlockBloke();
	m_pPlayer->Initialise(renderer, m_pWorld);

	return true;
}

void
SceneBlockBloke::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pPlayer->Process(deltaTime, inputSystem);
	m_pWorld->Step(deltaTime, 6, 2);
	m_pGroundSprite->Process(deltaTime);
}

void
SceneBlockBloke::Draw(Renderer& renderer)
{
	m_pPlayer->Draw(renderer);
	m_pGroundSprite->Draw(renderer);
	m_pCrate->Draw(renderer);
}

void
SceneBlockBloke::DebugDraw()
{
	ImGui::Text("Scene: Block Bloke");

	ImGui::InputFloat("Rotation speed", &m_rotationSpeed);

	//m_pPlayer->DebugDraw();
	m_pWorld->DebugDraw();
}