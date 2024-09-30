#include "particleemitter.h"

#include "sprite.h"
#include "renderer.h"
#include "particle.h"

ParticleEmitter::ParticleEmitter()
    : m_fMaxLifespan(3.0f), m_fAccelerationScalar(-10), m_iSpawnBatchSize(10), m_bIsSpawning(false), m_iParticlesSpawned(0), m_fEmitRate(10.0f)
{

}

ParticleEmitter::~ParticleEmitter()
{

}

void
ParticleEmitter::SetPosition(float x, float y)
{
    m_fX = x;
    m_fY = y;
}

bool
ParticleEmitter::Initialise(Renderer& renderer)
{
	m_pSharedSprite = renderer.CreateSprite("sprites\\ball.png");
    m_pSharedSprite->SetScale(0.05f);


	return true;
}

void
ParticleEmitter::Process(float deltaTime)
{
    // If spawning is triggered, process the time accumulation
    if (m_bIsSpawning) {
        m_fTimeAccumulator += deltaTime;

        float timeBetweenSpawns = 1.0f / m_fEmitRate;

        // Spawn particles at intervals based on m_fEmitRate
        if (m_iParticlesSpawned < m_iSpawnBatchSize && m_fTimeAccumulator >= timeBetweenSpawns) {
            SpawnParticle();
            m_fTimeAccumulator = 0.0f;
            m_iParticlesSpawned++;
        }

        // Stop spawning when the batch is complete
        if (m_iParticlesSpawned >= m_iSpawnBatchSize) {
            m_bIsSpawning = false;
            m_iParticlesSpawned = 0;
        }
    }

    for (auto it = m_particles.begin(); it != m_particles.end();)
    {
        Particle* particle = *it;
        if (particle->m_bAlive)
        {
            particle->Process(deltaTime);
            ++it;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void
ParticleEmitter::Draw(Renderer& renderer)
{
    for (Particle* particle : m_particles)
    {
        if (particle->m_bAlive)
        {
            particle->Draw(renderer);
        }
    }
}

void
ParticleEmitter::DebugDraw()
{

}

void 
ParticleEmitter::SpawnParticle()
{
    Particle* newParticle = new Particle();
    newParticle->Initialise(*m_pSharedSprite);
    newParticle->m_bAlive = true;
    newParticle->m_fMaxLifespan = m_fMaxLifespan;
    newParticle->m_position.x = m_fX;
    newParticle->m_position.y = m_fY;
    newParticle->m_acceleration.x = 1 * m_fAccelerationScalar;
    newParticle->m_acceleration.y = 1 * m_fAccelerationScalar;
    newParticle->m_fColour[0] = m_fColour[0];
    newParticle->m_fColour[1] = m_fColour[1];
    newParticle->m_fColour[2] = m_fColour[2];
    m_particles.push_back(newParticle);
}

void
ParticleEmitter::Spawn()
{
    // Trigger the spawning process
    m_bIsSpawning = true;
    m_iParticlesSpawned = 0;
    m_fTimeAccumulator = 0.0f;

}