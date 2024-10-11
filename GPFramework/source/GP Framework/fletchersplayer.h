#ifndef _FLETCHERSPLAYER_H
#define _FLETCHERSPLAYER_H

#include "entity.h"
#include "box2d/box2d.h"
#include "elementtype.h"
#include "animatedentity.h"
#include "animatedsprite.h"

#include "vector"

class Renderer;
class Sprite;
class SoundSystem;
class Shield;
class b2World;
class b2Body;
class b2PolygonShape;
class b2Vec2;
class b2Fixture;
class Explosion;
class SoundSystem;
class FletchsTestBlock;
class FletchersScene;


class FletchersPlayer : public AnimatedEntity
{
public:
	FletchersPlayer();
	FletchersPlayer(float x, float y);
	~FletchersPlayer();

	virtual bool Initialise(Renderer& renderer, b2World& world) override;
	bool Initialise(Renderer& renderer, b2World& world, Level& scene);
	void Process(float deltaTime, InputSystem& inputSystem, SoundSystem& soundSystem, Level& scene);
	virtual void Process(float deltaTime, InputSystem& inputSystem) override;
	virtual void Draw(Renderer& renderer) override;

	void CreateBoxWithEdges(b2Body* body, float width, float height);
	ElementType GetType() const;
	void Toggle(ElementType type) {};

	float m_fJumpStrength;

	void Jump();
	void Jump(SoundSystem& soundSystem);

protected:

private:
	FletchersPlayer(const FletchersPlayer& blockBloke);
	FletchersPlayer& operator=(const FletchersPlayer& blockBloke);

	bool IsKey1();
	bool IsKey2();
	bool IsKey3();

	void AnimationRunning();

	void AnimationFire();
	void AnimationEarth();
	void AnimationIce();

	void AnimateAnimationFire();
	void AnimateAnimationEarth();
	void AnimateAnimationIce();

public:

protected:
	b2Body* m_pBody;
	b2PolygonShape* m_pShape;
	b2Fixture* m_pFixture;
	b2Vec2 m_vVelocity;
	b2Vec2 m_vJump;
	ElementType m_eCurrentType;

	bool m_bHurt;

	float m_fTimeSinceJumpStarted;

	bool m_bSwitchingAnimation;

	bool m_bJumping;
	bool m_bFalling;

	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;

};

#endif // !_BLOCKBLOKE
