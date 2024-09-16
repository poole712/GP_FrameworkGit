#include "coalwalker.h"

#include "logmanager.h"
#include "renderer.h"
#include "animatedsprite.h"
#include "animatedentity.h"
#include "coalwalkermoving.h"
#include "coalwalkerattacking.h"
#include "soundsystem.h"
#include "fireball.h"
#include "blockbloke.h"
#include "inlinehelper.h"


CoalWalker::CoalWalker(bool goingLeft)
	: m_bGoingLeft(goingLeft)
{

	LogManager::GetInstance().Log("Enemy constructed");
}

CoalWalker::~CoalWalker()
{
	delete m_pMovingCoalWalker;
	m_pMovingCoalWalker = 0;

	delete m_pAttackingCoalWalker;
	m_pAttackingCoalWalker = 0;

	for (Fireball* fireball : m_pFireballs)
	{
		delete fireball;
		fireball = 0;
	}

}


bool
CoalWalker::Initialise(Renderer& renderer)
{
	m_iCurrentFBIndex = 0;

	m_pFireballs = std::vector<Fireball*>();
	for (int i = 0; i < 4; ++i)
	{
		Fireball* fireball = new Fireball(m_bGoingLeft);
		fireball->Initialise(renderer);
		m_pFireballs.push_back(fireball);
	}
	
	for (Fireball* fireball : m_pFireballs)
	{
		fireball->Initialise(renderer);
	}

	m_fFireCooldown = 3.0f;
	m_fFirstFireDelay = GetRandom(2, 6);

	m_pMovingCoalWalker = new CoalWalkerMoving(m_bGoingLeft);
	m_pMovingCoalWalker->Initialise(renderer); 
	m_pMovingCoalWalker->SetAliveState(true);

	m_pAttackingCoalWalker = new CoalWalkerAttacking(m_bGoingLeft);
	m_pAttackingCoalWalker->Initialise(renderer);
	


	return true;
}



void
CoalWalker::Process(float deltaTime, BlockBloke& player, SoundSystem& soundSystem)
{
	if(m_bIsAlive)
	{
		m_pMovingCoalWalker->Process(deltaTime);
		m_pAttackingCoalWalker->Process(deltaTime);

		m_fTimeSinceLastFire += deltaTime;
		m_fTimeToFirstFire += deltaTime;


		if (m_fTimeToFirstFire >= m_fFirstFireDelay && !m_bIsFiring)
		{
			StartAttacking();
			m_fTimeSinceLastFire = 0.0f;
		}

		if (m_fTimeSinceLastFire >= m_fFireCooldown && m_bIsFiring)
		{
			Attack();
			soundSystem.PlaySound("FireballShoot");
		}



		for (Fireball* fireball : m_pFireballs)
		{
			fireball->Process(deltaTime);

			if (fireball->IsAlive())
			{
				float distanceFromCW = fireball->GetPosition().x - m_pAttackingCoalWalker->GetPosition().x;
				if ((distanceFromCW <= 5 && m_bGoingLeft) || (distanceFromCW >= -5 && !m_bGoingLeft))
				{
					SetAlive(false);
					soundSystem.PlaySound("Fireball1");
				}
				if (fireball->IsCollidingWith(player))
				{
					if ((player.GetShieldAngle() < 140 && player.GetShieldAngle() > 30) && (m_bGoingLeft))
					{
						fireball->Deflect();
						soundSystem.PlaySound("Deflect");
						fireball->SetPosition(fireball->GetPosition().x - 15, fireball->GetPosition().y);
						return;
					}
					if ((player.GetShieldAngle() < -30 && player.GetShieldAngle() > -140) && (!m_bGoingLeft))
					{
						fireball->Deflect();
						soundSystem.PlaySound("Deflect");
						fireball->SetPosition(fireball->GetPosition().x + 15, fireball->GetPosition().y);
						return;
					}
					else
					{
						LogManager::GetInstance().Log("Hurt Player");
						player.Hurt(true, m_bGoingLeft, false, soundSystem);
						fireball->SetAliveState(false);
					}
				}
			}
		}
	}
}

void
CoalWalker::Draw(Renderer& renderer)
{
	if (m_bIsAlive)
	{
		m_pMovingCoalWalker->Draw(renderer);
		m_pAttackingCoalWalker->Draw(renderer);
		for (Fireball* fireball : m_pFireballs)
		{
			if (fireball->IsAlive())
			{
				fireball->Draw(renderer);
			}
		}
	}
	
}

bool
CoalWalker::GetAliveState()
{
	return m_bIsAlive;
}

void
CoalWalker::SetAlive(bool alive)
{
	m_bIsAlive = alive;
}

void
CoalWalker::StartAttacking()
{
	m_pMovingCoalWalker->SetAliveState(false);
	m_pAttackingCoalWalker->SetAliveState(true);
	m_pAttackingCoalWalker->SetPosition(m_pMovingCoalWalker->GetPosition().x, m_pMovingCoalWalker->GetPosition().y);

	//m_pAttackingCoalWalker.SetAliveState(true)
	//m_pAttackingCoalWalker.StartAttacking();

	m_bIsFiring = true; 
}

void CoalWalker::Attack()
{
	LogManager::GetInstance().Log("Attacking");
	if (m_iCurrentFBIndex > 3)
	{
		m_iCurrentFBIndex = 0;
	}
	int xModifier = m_bGoingLeft ? 50 : -50;
	m_pFireballs[m_iCurrentFBIndex]->SetPositionWithResetPos
		(m_pAttackingCoalWalker->GetPosition().x + xModifier, m_pAttackingCoalWalker->GetPosition().y - 15);
	m_iCurrentFBIndex++;
	m_fTimeSinceLastFire = 0.0f;

}

void CoalWalker::Die()
{
}
