#ifndef _PLAYER_H
#define _PLAYER_H

#include "animatedentity.h"
#include "animatedsprite.h"

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

	enum ActiveSpell
	{
		FIRE = 1,
		EARTH = 2,
		ICE = 3
	};

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

	ActiveSpell GetActiveSpell();

private:
	bool m_bSwitchingAnimation;
	ActiveSpell m_iActiveSpell;
};

#endif // _PLAYER_H