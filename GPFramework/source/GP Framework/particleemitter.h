#ifndef _PARTICLEEMITTER_H
#define _PARTICLEEMITTER_H

#include <vector>

class Renderer;
class Sprite;
class Particle;

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTIme);
	void Draw(Renderer& renderer);

	void SetPosition(float x, float y);

	void Spawn();
	void SpawnParticle();


	void DebugDraw();

protected:

private:
	ParticleEmitter(const ParticleEmitter& particleEmitter);
	ParticleEmitter& operator=(const ParticleEmitter& particleEmitter);

public:

protected:
	Sprite* m_pSharedSprite;
	std::vector<Particle*> m_particles;

	float m_fTimeElapsed;

	int m_iSpawnBatchSize;
	float m_fEmitRate;
	float m_fMaxLifespan;
	float m_fAccelerationScalar;
	float m_fColour[3];
	float m_fMinAngle;
	float m_fMaxAngle;
	float m_fX;
	float m_fY;
	bool m_bIsSpawning;
	int m_iParticlesSpawned;
	float m_fTimeSinceSpawned;
	float m_fTimeAccumulator;
	int m_iParticlesSpawnedInBatch;

private:

};
#endif // !_PARTICLEEMITTER_H
