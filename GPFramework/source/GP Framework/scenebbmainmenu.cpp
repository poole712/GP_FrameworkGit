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
}

bool 
SceneBBMainMenu::Initialise(Renderer& renderer)
{
	m_pTitleSprite = renderer.CreateSprite("sprites\\anim8strip.png");
	m_pTitleSprite->SetScale(1.0f);
	m_pTitleSprite->SetY(240);
	m_pTitleSprite->SetX(640);

	
	renderer.CreateStaticText("Play", 72);

	m_pPlayButton = renderer.CreateSprite("Play");
	m_pPlayButton->SetY(500);
	m_pPlayButton->SetX(640);
	return false;
}

void
SceneBBMainMenu::Process(float deltaTime, InputSystem& inputSystem, int& scene)
{
    m_pPlayButton->Process(deltaTime);
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
        if (IsMouseOverObject(mouseX, mouseY, *m_pPlayButton))
        {
			scene = 1;
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
}

void 
SceneBBMainMenu::DebugDraw()
{

}
