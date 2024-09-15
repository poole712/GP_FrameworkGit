#ifndef _BLOCKBLOKE_H
#define _BLOCKBLOKE_H

#include "entity.h"
#include "vector"

class Renderer;
class Sprite;
class SoundSystem;
class Shield;
class b2World;
class b2Body;
class b2PolygonShape;
class b2Fixture;
class Explosion;
class SoundSystem;


class BlockBloke : public Entity
{
public:
	BlockBloke();
	~BlockBloke();

	virtual bool Initialise(Renderer& renderer) override;
	bool Initialise(Renderer& renderer, b2World* world);
	void Process(float deltaTime, InputSystem& inputSystem, SoundSystem& soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;
	void Hurt(bool fireball, bool fireballLeft, bool bomb, SoundSystem& soundSystem);
	virtual void Draw(Renderer& renderer) override;
	void ShootBullet(SoundSystem& soundSystem);

	float m_fJumpStrength;
	float m_fRotationSpeed;
	float GetShieldAngle();

protected:
	void FireDelay(int milliseconds);
	void Move(float x);
	void Jump(SoundSystem& soundSystem);

	void HurtVisuals(bool on);
 


private:
	BlockBloke(const BlockBloke& blockBloke);
	BlockBloke& operator=(const BlockBloke& blockBloke);

public:

protected:
	Shield* m_pShield;
	Sprite* m_pLeftR1;
	Sprite* m_pLeftR2;
	Sprite* m_pRightR1;
	Sprite* m_pRightR2;
	b2Body* m_pBody;
	b2PolygonShape* m_pShape;
	b2Fixture* m_pFixture;

	Explosion* m_pLeftExplosion;
	Explosion* m_pRightExplosion;
	Explosion* m_pTopExplosion;

	bool m_bHurt;

	int m_iHealth;
	int m_iAmmo;

	bool m_bCanFire;
	bool m_bJumping;
	bool m_bCanPlayRotSfx;


	float m_fTimeSinceLastHurt;
	float m_fHurtCooldown;

	float m_fTimeSinceLastFire;
	float m_fFireCooldown;

	float m_fTimeSinceJumpStarted;
	float m_fJumpLength;
	
	float m_fTimeSinceRotSfxPlayed;
	float m_fRotSfxCooldown;

	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;

};

#endif // !_BLOCKBLOKE
