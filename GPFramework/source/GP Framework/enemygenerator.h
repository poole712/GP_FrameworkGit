#ifndef _ENEMYGENERATOR_H
#define _ENEMYGENERATOR_H

#include "vector"
#include "enemy.h"

class SoundSystem;
class Renderer;
class Enemy;
class AnimatedEntity;
class CoalWalkerMoving;
class CoalWalkerAttacking;
class Bomb;
class CoalWalker;
class WolfRunner;
class BlockBloke;
class SoundSystem;

class EnemyGenerator
{
public:
	EnemyGenerator();
	~EnemyGenerator();

	bool Initialise(Renderer& renderer);
	bool GetRandomBool();
	void Process(float deltaTime, BlockBloke& player, SoundSystem& soundSystem);
	void Draw(Renderer& renderer);
	void SpawnEnemy();

protected:
	int FireDelay(int min, int max);


private:
	EnemyGenerator(const EnemyGenerator& blockBloke);
	EnemyGenerator& operator=(const EnemyGenerator& blockBloke);

public:

protected:
	int m_iCurrentCoalIndex;
	int m_iCurrentWolfIndex;
	int m_iCurrentBombIndex;

	std::vector<CoalWalker*> m_pCoalWalkers;
	std::vector<WolfRunner*> m_pWolfRunners;
	std::vector<Bomb*> m_pBombs;

	float m_fTimeSinceLastSpawn;
	float m_fFireCooldown;


};

#endif // !_ENEMYGENERATOR_H
