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

	void AnimationCount0to3();

	void AnimationCount4to5();
	void AnimationCount5to6();
	void AnimationCount6to7();

	void AnimateAnimationFire();
	void AnimateAnimationEarth();
	void AnimateAnimationIce();

	ElementType GetActiveSpell() const;

private:
	bool m_bSwitchingAnimation;
	ElementType m_iActiveSpell;
};

#endif // _PLAYER_H