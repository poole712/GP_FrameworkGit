#include "hud.h"

#include "sprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "logmanager.h"
#include "game.h"

#include <SDL_scancode.h>


Hud::Hud()
{
}

Hud::~Hud()
{
	delete m_pFireControls;
	m_pFireControls = 0;

	delete m_pEarthControls;
	m_pEarthControls = 0;

	delete m_pIceControls;
	m_pIceControls = 0;
}

bool
Hud::Initialise(Renderer& renderer)
{
	renderer.CreateStaticText("1. Fire", 48);
	renderer.CreateStaticText("2. Earth", 48);
	renderer.CreateStaticText("3. Ice", 48);

	m_pFireControls = renderer.CreateSprite("1. Fire");
	m_pEarthControls = renderer.CreateSprite("2. Earth");
	m_pIceControls = renderer.CreateSprite("3. Ice");

	m_pFireControls->SetY(100);
	m_pFireControls->SetX(100);
	m_pFireControls->SetGreenTint(0.25f);
	m_pFireControls->SetBlueTint(0.25f);

	m_pEarthControls->SetY(150);
	m_pEarthControls->SetX(130);
	m_pEarthControls->SetRedTint(0.25f);
	m_pEarthControls->SetBlueTint(0.25f);

	m_pIceControls->SetY(200);
	m_pIceControls->SetX(100);
	m_pIceControls->SetGreenTint(0.25f);
	m_pIceControls->SetRedTint(0.25f);

	return false;
}

void
Hud::Process(float deltaTime, InputSystem& inputSystem, Game& game)
{
	m_pFireControls->Process(deltaTime);
	m_pEarthControls->Process(deltaTime);
	m_pIceControls->Process(deltaTime);
}


void
Hud::Draw(Renderer& renderer)
{
	m_pFireControls->Draw(renderer);
	m_pEarthControls->Draw(renderer);
	m_pIceControls->Draw(renderer);
}
