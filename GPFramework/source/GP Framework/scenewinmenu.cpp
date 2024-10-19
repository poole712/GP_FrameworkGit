#include "scenewinmenu.h"

#include "sprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "logmanager.h"
#include "uihandler.h"
#include "game.h"
#include "background.h"
#include <string>
#include "levelparser.h"

#include <SDL_scancode.h>


SceneWinMenu::SceneWinMenu()
{
}

SceneWinMenu::~SceneWinMenu()
{
	delete m_pTitleSprite;
	m_pTitleSprite = 0;

	delete m_pQuitToMenuButton;
	m_pQuitToMenuButton = 0;
}

bool
SceneWinMenu::Initialise(Renderer& renderer)
{
	renderer.CreateStaticText("You won!", 72);
	renderer.CreateStaticText("Quit to Menu", 48);

	m_bBackground = new Background();
	m_bBackground->Initialise(renderer);

	m_pTitleSprite = renderer.CreateSprite("You won!");
	m_pQuitToMenuButton = renderer.CreateSprite("Quit to Menu");


	m_pTitleSprite->SetY(400);
	m_pTitleSprite->SetX(960);

	m_pQuitToMenuButton->SetY(700);
	m_pQuitToMenuButton->SetX(960);

	return true;
}

void
SceneWinMenu::Process(float deltaTime, InputSystem& inputSystem, Game& game)
{
	m_pQuitToMenuButton->Process(deltaTime);

	m_pTitleSprite->Process(deltaTime);

	m_bBackground->Process(deltaTime);


	// Retrieve mouse button state for the left mouse button (usually index 0)
	ButtonState mouseState = inputSystem.GetMouseButtonState(1);
	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));

	// Get mouse position
	int mouseX = inputSystem.GetMousePosition().x;
	int mouseY = inputSystem.GetMousePosition().y;

	m_pQuitToMenuButton->SetGreenTint(100);
	m_pQuitToMenuButton->SetBlueTint(100);

	if (IsMouseOverObject(mouseX, mouseY, *m_pQuitToMenuButton))
	{
		m_pQuitToMenuButton->SetGreenTint(0);
		m_pQuitToMenuButton->SetBlueTint(0);
	}

	// Check if the left mouse button was pressed
	if (mouseState == BS_PRESSED)  // Ensure this matches your ButtonState enum
	{
		// Check if the mouse is over the play button
		if (IsMouseOverObject(mouseX, mouseY, *m_pQuitToMenuButton))
		{
			game.SwitchScene(0);
		}
	}
}


bool
SceneWinMenu::IsMouseOverObject(float mouseX, float mouseY, const Sprite& object)
{
	float objX = object.GetX();
	float objY = object.GetY();
	float objWidth = object.GetWidth();
	float objHeight = object.GetHeight();

	return (mouseX >= objX - objWidth / 2 && mouseX <= objX + objWidth / 2 &&
		mouseY >= objY - objHeight / 2 && mouseY <= objY + objHeight / 2);
}

void
SceneWinMenu::Draw(Renderer& renderer)
{
	m_bBackground->Draw(renderer);
	m_pTitleSprite->Draw(renderer);
	m_pQuitToMenuButton->Draw(renderer);
}

void
SceneWinMenu::DebugDraw()
{

}
