#include "scenedeathmenu.h"

#include "sprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "logmanager.h"
#include "uihandler.h"
#include "game.h"

#include <SDL_scancode.h>


SceneDeathMenu::SceneDeathMenu()
{
}

SceneDeathMenu::~SceneDeathMenu()
{
	delete m_pTitleSprite;
	m_pTitleSprite = 0;

	delete m_pRetryButton;
	m_pRetryButton = 0;

	delete m_pQuitToMenuButton;
	m_pQuitToMenuButton = 0;
}

bool
SceneDeathMenu::Initialise(Renderer& renderer)
{
	renderer.CreateStaticText("You died!", 72);
	renderer.CreateStaticText("Retry", 48);
	renderer.CreateStaticText("Quit to Menu", 48);

	m_pTitleSprite = renderer.CreateSprite("You died!");
	m_pRetryButton = renderer.CreateSprite("Retry");
	m_pQuitToMenuButton = renderer.CreateSprite("Quit to Menu");

	m_pTitleSprite->SetY(400);
	m_pTitleSprite->SetX(960);

	m_pRetryButton->SetY(600);
	m_pRetryButton->SetX(960);

	m_pQuitToMenuButton->SetY(700);
	m_pQuitToMenuButton->SetX(960);

	return true;
}

void
SceneDeathMenu::Process(float deltaTime, InputSystem& inputSystem, Game& game)
{
	m_pRetryButton->Process(deltaTime);
	m_pQuitToMenuButton->Process(deltaTime);

	m_pTitleSprite->Process(deltaTime);

	// Retrieve mouse button state for the left mouse button (usually index 0)
	ButtonState mouseState = inputSystem.GetMouseButtonState(1);
	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));

	// Get mouse position
	int mouseX = inputSystem.GetMousePosition().x;
	int mouseY = inputSystem.GetMousePosition().y;

	// Check if the left mouse button was pressed
	if (mouseState == BS_PRESSED)  // Ensure this matches your ButtonState enum
	{
		// Check if the mouse is over the play button
		if (IsMouseOverObject(mouseX, mouseY, *m_pQuitToMenuButton))
		{
			game.SwitchScene(0);
		}
		if (IsMouseOverObject(mouseX, mouseY, *m_pRetryButton))
		{
			game.SwitchScene(1);
		}
	}
}


bool
SceneDeathMenu::IsMouseOverObject(int mouseX, int mouseY, const Sprite& object)
{
	// Assuming the object has x, y, width, height properties
	return (mouseX >= object.GetX() && mouseX <= object.GetX() + object.GetWidth() &&
		mouseY >= object.GetY() && mouseY <= object.GetY() + object.GetHeight());
}

void
SceneDeathMenu::Draw(Renderer& renderer)
{
	m_pTitleSprite->Draw(renderer);
	m_pRetryButton->Draw(renderer);
	m_pQuitToMenuButton->Draw(renderer);
}

void
SceneDeathMenu::DebugDraw()
{

}
