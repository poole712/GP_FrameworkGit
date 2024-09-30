/*#include "explosion.h"

#include "renderer.h"
#include "animatedsprite.h"

Explosion::Explosion()
{
}

Explosion::~Explosion()
{

}

bool 
Explosion::Initialise(Renderer& renderer)
{
	m_pASprite = renderer.CreateAnimatedSprite("sprites\\Explosion.png");
	m_pASprite->SetupFrames(128, 128);
	m_pASprite->SetFrameDuration(0.1f);
	m_pASprite->SetScale(1.0f);
	m_pASprite->SetLooping(false);
	return true;
}

void 
Explosion::Process(float deltaTime)
{
	if (m_bAlive)
	{
		AnimatedEntity::Process(deltaTime);
	}
}

void 
Explosion::Draw(Renderer& renderer)
{
	
	AnimatedEntity::Draw(renderer);
}

void 
Explosion::SetAlive(bool alive)
{
	m_pASprite->Restart();
	m_bAlive = alive;
}

void 
Explosion::SetThePosition(float x, float y)
{
	SetPosition(x, y);
}
*/