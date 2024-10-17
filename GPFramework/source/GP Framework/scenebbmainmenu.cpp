#include "scenebbmainmenu.h"

#include "sprite.h"
#include "renderer.h"
#include "inputsystem.h"
#include "soundsystem.h"
#include "logmanager.h"
#include "uihandler.h"
#include "game.h"
#include "background.h"

#include "imgui/imgui_impl_sdl2.h"

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
	
	delete m_pSoundSystem;
	m_pSoundSystem = 0;

	delete m_iInputSystem;
	m_iInputSystem = 0;
}

bool 
SceneBBMainMenu::Initialise(Renderer& renderer)
{
	renderer.CreateStaticText("Mage Runner", 150);
	renderer.CreateStaticText("Play", 72);
	renderer.CreateStaticText("Quit", 72);

	m_bBackground = new Background();
	m_bBackground->Initialise(renderer);

	m_iInputSystem = new InputSystem();
	m_iInputSystem->Initialise();

	m_pSoundSystem = new SoundSystem();
	m_pSoundSystem->Initialise();
	m_pSoundSystem->CreateSound("sounds\\MainMenuMusic.mp3", "Menu Music");
	m_pSoundSystem->PlaySound("Menu Music");

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

	m_bBackground->Process(deltaTime);

	m_pSoundSystem->Process(deltaTime);

    // Retrieve mouse button state for the left mouse button (usually index 0)
    ButtonState mouseState = inputSystem.GetMouseButtonState(1);
	ButtonState spaceState = (inputSystem.GetKeyState(SDL_SCANCODE_SPACE));

    // Get mouse position
    int mouseX = inputSystem.GetMousePosition().x;
    int mouseY = inputSystem.GetMousePosition().y;

	m_pPlayButton->SetRedTint(100);

	m_pQuitButton->SetGreenTint(100);
	m_pQuitButton->SetBlueTint(100);

	if (IsMouseOverObject(mouseX, mouseY, *m_pPlayButton))
	{
		m_pPlayButton->SetRedTint(0);
	}
	else if (IsMouseOverObject(mouseX, mouseY, *m_pQuitButton))
	{
		m_pQuitButton->SetGreenTint(0);
		m_pQuitButton->SetBlueTint(0);
	}

    // Check if the left mouse button was pressed
    if (mouseState == BS_PRESSED)  // Ensure this matches your ButtonState enum
    {
        // Check if the mouse is over the play button
        if (IsMouseOverObject(mouseX, mouseY, *m_pPlayButton))
        {
			m_pSoundSystem->PauseSound("Menu Music", true);
			m_pSoundSystem->StopAllSound();
			game.SwitchScene(1);
        }
		if (IsMouseOverObject(mouseX, mouseY, *m_pQuitButton))
		{
			game.Quit();
		}
    }
}


bool 
SceneBBMainMenu::IsMouseOverObject(float mouseX, float mouseY, const Sprite& object)
{
	float objX = object.GetX();
	float objY = object.GetY();
	float objWidth = object.GetWidth();
	float objHeight = object.GetHeight();

	return (mouseX >= objX - objWidth/2 && mouseX <= objX + objWidth/2 &&
		mouseY >= objY - objHeight/2 && mouseY <= objY + objHeight/2);
}

void 
SceneBBMainMenu::Draw(Renderer& renderer)
{
	m_bBackground->Draw(renderer);
	m_pPlayButton->Draw(renderer);
	m_pTitleSprite->Draw(renderer);
	m_pQuitButton->Draw(renderer);
}

void 
SceneBBMainMenu::DebugDraw()
{
	ImGui::Text("Play X: %f, Play Y: %f", m_pPlayButton->GetX(), m_pPlayButton->GetY());
	ImGui::Text("Width: %f, Height: %f", m_pPlayButton->GetWidth(), m_pPlayButton->GetHeight());

	ImGui::Text("Mouse X: %f, Mouse Y: %f", m_iInputSystem->GetMousePosition().x, m_iInputSystem->GetMousePosition().y);
}
