#include "scenebbmainmenu.h"

#include "sprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "logmanager.h"
#include "uihandler.h"
#include "game.h"

#include <SDL_scancode.h>


SceneBBMainMenu::SceneBBMainMenu()
{
}

SceneBBMainMenu::~SceneBBMainMenu()
{
	delete m_pTitleSprite;
	m_pTitleSprite = 0;

	delete m_pPlayButton;
	m_pPlayButton = 0;

	delete m_pQuitButton;
	m_pQuitButton = 0;
}

bool 
SceneBBMainMenu::Initialise(Renderer& renderer)
{
	renderer.CreateStaticText("Mage Runner", 150);
	renderer.CreateStaticText("Play", 72);
	renderer.CreateStaticText("Quit", 72);

	m_pTitleSprite = renderer.CreateSprite("Mage Runner");
	m_pPlayButton = renderer.CreateSprite("Play");
	m_pQuitButton = renderer.CreateSprite("Quit");

	m_pTitleSprite->SetY(240);
	m_pTitleSprite->SetX(960);

	m_pPlayButton->SetY(600);
	m_pPlayButton->SetX(960);

	m_pQuitButton->SetY(700);
	m_pQuitButton->SetX(960);

	return false;
}

void
SceneBBMainMenu::Process(float deltaTime, InputSystem& inputSystem, Game& game)
{
    m_pPlayButton->Process(deltaTime);
    m_pTitleSprite->Process(deltaTime);
	m_pQuitButton->Process(deltaTime);


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
        if (IsMouseOverObject(mouseX, mouseY, *m_pPlayButton))
        {
			game.SwitchScene(1);
        }
		if (IsMouseOverObject(mouseX, mouseY, *m_pQuitButton))
		{
			game.Quit();
		}
    }
}


bool 
SceneBBMainMenu::IsMouseOverObject(int mouseX, int mouseY, const Sprite& object)
{
	// Assuming the object has x, y, width, height properties
	return (mouseX >= object.GetX() && mouseX <= object.GetX() + object.GetWidth() &&
		mouseY >= object.GetY() && mouseY <= object.GetY() + object.GetHeight());
}

void 
SceneBBMainMenu::Draw(Renderer& renderer)
{
	m_pPlayButton->Draw(renderer);
	m_pTitleSprite->Draw(renderer);
	m_pQuitButton->Draw(renderer);
}

void 
SceneBBMainMenu::DebugDraw()
{

}
