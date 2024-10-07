#ifndef _PLAYER_H
#define _PLAYER_H

#include "animatedentity.h"
#include "animatedsprite.h"

#include "elementtype.h"

class Renderer;
class Sprite;
class InputSystem;
class AnimatedSprite;
class AnimatedEntity;

class Player : public AnimatedEntity
{
public:
	Player();
	~Player();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	bool IsKey1();
	bool IsKey2();
	bool IsKey3();
	bool IsKeySpace();

	void AnimationRunning();
	void AnimationJump();
	void AnimationFall();

	void AnimationFire();
	void AnimationEarth();
	void AnimationIce();

	void AnimateAnimationFire();
	void AnimateAnimationEarth();
	void AnimateAnimationIce();

	void AnimateAnimationJump();
	void AnimateAnimationFall();

	ElementType GetActiveSpell() const;

private:
	bool m_bSwitchingAnimation;

	bool m_bJumping;
	bool m_bFalling;

	ElementType m_iActiveSpell;
};

#endif // _PLAYER_H