#include "enemygenerator.h"

#include "logmanager.h"
#include "renderer.h"
#include "animatedsprite.h"
#include "animatedentity.h"
#include "coalwalker.h"
#include "wolfrunner.h"
#include "bomb.h"
#include "blockbloke.h"
#include "inlinehelper.h"
#include "soundsystem.h"
#include <iostream>
#include <random>


EnemyGenerator::EnemyGenerator()
{

	LogManager::GetInstance().Log("Enemy constructed");
}

EnemyGenerator::~EnemyGenerator()
{
	for (CoalWalker* cw : m_pCoalWalkers)
	{
		delete cw;
		cw = 0;
	}

	for (WolfRunner* wr : m_pWolfRunners)
	{
		delete wr;
		wr = 0;
	}

	for (Bomb* bomb : m_pBombs)
	{
		delete bomb;
		bomb = 0;
	}
}


bool
EnemyGenerator::Initialise(Renderer& renderer)
{
	m_fFireCooldown = GetRandom(2, 5);

	//Coal Walkers
	m_pCoalWalkers = std::vector<CoalWalker*>();
	for (int i = 0; i < 49; ++i)
	{
		CoalWalker* cw = new CoalWalker(GetRandomBool());
		cw->Initialise(renderer);
		m_pCoalWalkers.push_back(cw);
	}
	for (CoalWalker* cw : m_pCoalWalkers)
	{
		cw->Initialise(renderer);
	}

	//Wolf Runners
	m_pWolfRunners = std::vector<WolfRunner*>();
	for (int i = 0; i < 49; ++i)
	{
		WolfRunner* wr = new WolfRunner(GetRandomBool());
		wr->Initialise(renderer);
		m_pWolfRunners.push_back(wr);
	}
	for (WolfRunner* wr : m_pWolfRunners)
	{
		wr->Initialise(renderer);
	}

	//Bombs
	m_pBombs = std::vector<Bomb*>();
	for (int i = 0; i < 49; ++i)
	{
		Bomb* bomb = new Bomb();
		bomb->Initialise(renderer);
		m_pBombs.push_back(bomb);
	}
	for (Bomb* cw : m_pBombs)
	{
		cw->Initialise(renderer);
	}

	return true;
}

bool
EnemyGenerator::GetRandomBool()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::bernoulli_distribution dist(0.5); 
	return dist(gen);
}



void
EnemyGenerator::Process(float deltaTime, BlockBloke& player, SoundSystem& soundSystem)
{

	m_fTimeSinceLastSpawn += deltaTime;

	for (CoalWalker* cw : m_pCoalWalkers)
	{
		if (cw->GetAliveState())
		{
			cw->Process(deltaTime, player, soundSystem);
		}
	}
	for (WolfRunner* wr : m_pWolfRunners)
	{
		if (wr->IsAlive())
		{
			wr->Process(deltaTime);
			if (wr->IsCollidingWith(player))
			{
				wr->SetAliveState(false);
				
				player.Hurt(false, false, false, soundSystem);
				//player.Hurt();
			}
		}
	}
	for (Bomb* bomb : m_pBombs)
	{
		if (bomb->IsAlive())
		{
			bomb->Process(deltaTime);
			if (bomb->IsCollidingWith(player))
			{
				if (player.GetShieldAngle() >= 130 && player.GetShieldAngle() <= 210)
				{
					bomb->Deflect();
					soundSystem.PlaySound("Deflect");
				}
				else
				{
					bomb->SetHitPlayer();
					player.Hurt(false, false, true, soundSystem);
					//player.Hurt();
				}
			}
		}
	}

	if (m_fTimeSinceLastSpawn >= m_fFireCooldown)
	{
		SpawnEnemy();
	}

}



void
EnemyGenerator::Draw(Renderer& renderer)
{
	for (CoalWalker* cw : m_pCoalWalkers)
	{
		if (cw->GetAliveState())
		{
			cw->Draw(renderer);
		}
	}
	for (WolfRunner* wr : m_pWolfRunners)
	{
		if (wr->IsAlive())
		{
			wr->Draw(renderer);
		}
	}
	for (Bomb* bomb : m_pBombs)
	{
		if (bomb->IsAlive())
		{
			bomb->Draw(renderer);
		}
	}
}

void
EnemyGenerator::SpawnEnemy()
{
	int randEnemyIndex = GetRandom(1, 3);

	switch (randEnemyIndex)
	{
	case 1:
		if (m_iCurrentCoalIndex < 48)
		{
			m_pCoalWalkers[m_iCurrentCoalIndex++]->SetAlive(true);
		}
		break;
	case 2:
		if (m_iCurrentWolfIndex < 48)
		{
			m_pWolfRunners[m_iCurrentWolfIndex++]->SetAliveState(true);
		}
		break;
	case 3:
		if (m_iCurrentBombIndex < 48)
		{
			m_pBombs[m_iCurrentBombIndex++]->SetAliveState(true);
		}
		break;
	}
	m_fFireCooldown = GetRandom(2, 5);
	m_fTimeSinceLastSpawn = 0;
}