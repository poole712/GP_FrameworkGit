#include "scenebbmainmenu.h"

#include "sprite.h"
#include "renderer.h"
#include "uihandler.h"

SceneBBMainMenu::SceneBBMainMenu()
{
}

SceneBBMainMenu::~SceneBBMainMenu()
{
}

bool SceneBBMainMenu::Initialise(Renderer& renderer)
{
	m_pTitleSprite = renderer.CreateSprite("sprites\\MenuTitle.png");
	m_pTitleSprite->SetX(640);
	m_pTitleSprite->SetScale(1.0f);
	m_pTitleSprite->SetY(240);
	//m_pTitleSprite->SetAngle(180.0f);
	//renderer.CreateStaticText("Play", 72);

	//m_pPlayButton = renderer.CreateSprite("Play");

	return false;
}

void SceneBBMainMenu::Process(float deltaTime, InputSystem& inputSystem)
{
	//m_pPlayButton->Process(deltaTime);
	m_pTitleSprite->Process(deltaTime);
}

void SceneBBMainMenu::Draw(Renderer& renderer)
{
	//m_pPlayButton->Draw(renderer);
	m_pTitleSprite->Draw(renderer);
}

void SceneBBMainMenu::DebugDraw()
{

}
