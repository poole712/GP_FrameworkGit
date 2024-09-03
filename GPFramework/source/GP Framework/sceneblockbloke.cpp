#include "sceneblockbloke.h"

#include "renderer.h"
#include "sprite.h"
#include "imgui/imgui.h"

#include <cassert>

SceneBlockBloke::SceneBlockBloke()
	: m_pCorners{ 0 }, m_pCentre(0), m_angle(0.0f), m_rotationSpeed(0.0f)
{

}

SceneBlockBloke::~SceneBlockBloke()
{
	for (int k = 0; k < 4; ++k)
	{
		delete m_pCorners[k];
		m_pCorners[k] = 0;
	}

	delete m_pCentre;
	m_pCentre = 0;
}

bool
SceneBlockBloke::Initialise(Renderer& renderer)
{
	m_pCentre = renderer.CreateSprite("sprites\\board8x8.png");
	m_pCorners[0] = renderer.CreateSprite("sprites\\board8x8.png");
	m_pCorners[1] = renderer.CreateSprite("sprites\\board8x8.png");
	m_pCorners[2] = renderer.CreateSprite("sprites\\board8x8.png");
	m_pCorners[3] = renderer.CreateSprite("sprites\\board8x8.png");

	const int BOARD_HALF_WIDTH = m_pCentre->GetWidth() / 2;
	const int BOARD_HALF_HEIGHT = m_pCentre->GetHeight() / 2;
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_pCentre->SetX(SCREEN_WIDTH / 2);
	m_pCentre->SetY(SCREEN_HEIGHT / 2);

	m_pCorners[0]->SetX(BOARD_HALF_WIDTH);
	m_pCorners[0]->SetY(BOARD_HALF_HEIGHT);

	m_pCorners[1]->SetX(BOARD_HALF_WIDTH);
	m_pCorners[1]->SetY(SCREEN_HEIGHT - BOARD_HALF_HEIGHT);
	m_pCorners[1]->SetGreenTint(0.0f);
	m_pCorners[1]->SetBlueTint(0.0f);

	m_pCorners[2]->SetX(SCREEN_WIDTH - BOARD_HALF_WIDTH);
	m_pCorners[2]->SetY(SCREEN_HEIGHT - BOARD_HALF_HEIGHT);
	m_pCorners[2]->SetRedTint(0.0f);
	m_pCorners[2]->SetBlueTint(0.0f);

	m_pCorners[3]->SetX(SCREEN_WIDTH - BOARD_HALF_WIDTH);
	m_pCorners[3]->SetY(BOARD_HALF_HEIGHT);
	m_pCorners[3]->SetGreenTint(0.0f);
	m_pCorners[3]->SetRedTint(0.0f);

	return true;
}

void
SceneBlockBloke::Process(float deltaTime, InputSystem& inputSystem)
{
	for (int k = 0; k < 4; ++k)
	{
		m_pCorners[k]->Process(deltaTime);
	}

	m_angle += m_rotationSpeed * deltaTime;

	m_pCentre->SetAngle(m_angle);
	m_pCentre->Process(deltaTime);
}

void
SceneBlockBloke::Draw(Renderer& renderer)
{
	for (int k = 0; k < 4; ++k)
	{
		m_pCorners[k]->Draw(renderer);
	}

	m_pCentre->Draw(renderer);
}

void
SceneBlockBloke::DebugDraw()
{
	ImGui::Text("Scene: Block Bloke");

	ImGui::InputFloat("Rotation speed", &m_rotationSpeed);

	
}