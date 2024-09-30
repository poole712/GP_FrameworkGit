#ifndef  _PARTICLE_H_
#define _PARTICLE_H_

#include "vector2.h"

class Renderer;
class Sprite;

class Particle
{
public: 
	Particle();
	~Particle();

	bool Initialise(Sprite& sprite);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

protected:

private:
	Particle(const Particle& particle);
	Particle& operator=(const Particle& particle);

public:
	Sprite* m_pSharedSprite;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;
	float m_fMaxLifespan;
	float m_fCurrentAge;
	float m_fColour[3];
	bool m_bAlive;

protected:

private:


};

#endif // ! _PARTICLE_H_
