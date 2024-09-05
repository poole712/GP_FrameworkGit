#include "sceneblockbloke.h"

#include "renderer.h"
#include "sprite.h"
#include "imgui/imgui.h"
#include <box2d/b2_draw.h>
#include "blockbloke.h"
#include "box2d/box2d.h"
#include "crate.h"

#include <cassert>

MyDebugDraw* SceneBlockBloke::debugDraw{};

class MyDebugDraw : public b2Draw
{
public: 

    MyDebugDraw(Renderer& renderer)
        : renderer(renderer)
    {

    }
    // Inherited via b2Draw
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
    {
        renderer.DrawPolygon(vertices, vertexCount, color);
    }
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
    {
        renderer.DrawSolidPolygon(vertices, vertexCount, color);
    }
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override
    {
        renderer.DrawCircle(center, radius, color);
    }
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override
    {
        renderer.DrawSolidCircle(center, radius, axis, color);
    }
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override
    {
        renderer.DrawSegment(p1, p2, color);
    }
    void DrawTransform(const b2Transform& xf) override
    {
        renderer.DrawTransform(xf);
    }
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override
    {
       renderer.DrawPoint(p, size, color);
    }

private:
    Renderer& renderer;
};


SceneBlockBloke::SceneBlockBloke()
    : m_angle(0.0f), m_rotationSpeed(0.0f)
{
}

SceneBlockBloke::~SceneBlockBloke()
{
    delete m_pPlayer;
    m_pPlayer = 0;

    delete m_pWorld;
    m_pWorld = 0;

    delete m_pCrate;
    m_pCrate = 0;

    delete m_pGround;
    m_pGround = 0;

    delete m_pGroundSprite;
    m_pGroundSprite = 0;

    m_pWorld->~b2World();

    delete debugDraw;
    debugDraw = 0;
}

bool
SceneBlockBloke::Initialise(Renderer& renderer)
{
    // Physics:
    b2Vec2 gravity;
    gravity.Set(0.0f, 100.0f);
    m_pWorld = new b2World(gravity);

    m_pBackgroundSprite = renderer.CreateSprite("sprites\\dirt.png");
    m_pBackgroundSprite->SetX(640.0f);
    m_pBackgroundSprite->SetY(600.0f);
    m_pBackgroundSprite->SetScale(2.0f);

    b2BodyDef ground;
    ground.position.Set(640.0f, 580.0f);
    b2Body* body = m_pWorld->CreateBody(&ground);

    m_pGround = new b2PolygonShape();
    m_pGround->SetAsBox(100.0f, 5.0f);
    body->CreateFixture(m_pGround, 0.0f);

    m_pCrate = new Crate();
    m_pCrate->Initialise(m_pWorld, renderer);

    m_pGroundSprite = renderer.CreateSprite("sprites\\board8x2.png");
    m_pGroundSprite->SetX(640.0f);
    m_pGroundSprite->SetY(600.0f);
    m_pGroundSprite->SetScale(0.1f);

    m_pPlayer = new BlockBloke();
    m_pPlayer->Initialise(renderer, m_pWorld);

    // Set up the debug draw
    

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
    m_pBackgroundSprite->Draw(renderer);
    m_pCrate->Draw(renderer);

    m_pPlayer->Draw(renderer);
    m_pGroundSprite->Draw(renderer);

    if (!debugDraw)
    {
        debugDraw = new MyDebugDraw(renderer);
        debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit);
        m_pWorld->SetDebugDraw(debugDraw);

    }
    
    m_pWorld->DebugDraw();




}

void
SceneBlockBloke::DebugDraw()
{
    ImGui::Text("Scene: Block Bloke");
    

    ImGui::InputFloat("Rotation speed", &m_rotationSpeed);

    //m_pWorld->DebugDraw();
    //m_pPlayer->DebugDraw();
}
