//#include "sceneplayeranimation.h"
//
//#include "player.h"
//#include "renderer.h"
//
//ScenePlayerAnimation::ScenePlayerAnimation()
//	: m_pPlayer(0)
//{
//}
//
//ScenePlayerAnimation::~ScenePlayerAnimation()
//{
//	delete m_pPlayer;
//	m_pPlayer = 0;
//
//	delete m_rRenderer;
//	m_rRenderer = 0;
//}
//
//bool ScenePlayerAnimation::Initialise(Renderer& renderer)
//{
//	m_rRenderer = &renderer;
//
//	m_pPlayer = new Player();
//	m_pPlayer->Initialise(renderer);
//
//	m_pPlayer->SetPosition(m_rRenderer->GetWidth()/2, m_rRenderer->GetHeight()/2);
//	return true;
//}
//
//void ScenePlayerAnimation::Process(float deltaTime, InputSystem& inputSystem, Game& game)
//{
//	m_pPlayer->Process(deltaTime);
//}
//
//void ScenePlayerAnimation::Draw(Renderer& renderer)
//{
//	m_pPlayer->Draw(renderer);
//}
//
//void ScenePlayerAnimation::DebugDraw()
//{
//}
