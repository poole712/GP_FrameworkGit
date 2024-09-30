#ifndef _ANIMATEDSPRITE_H
#define _ANIMATEDSPRITE_H

#include "sprite.h"

class Renderer;
class VertexArray;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void SetupFrames(int fixedFrameWidth, int fixedFrameHeight);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void SetLooping(bool loop);
	void Animate();
	bool IsAnimating() const;
	void Restart();
	void SetFrameDuration(float seconds);
	int GetWidth() const;
	int GetHeight() const;
	void DebugDraw();

	void SetAnimationRange(int startFrame, int endFrame);

protected:

private:
	AnimatedSprite(const AnimatedSprite& animatedsprite);
	AnimatedSprite& operator=(const AnimatedSprite& animatedsprite);

public:

protected:
	VertexArray* m_pVertexData;
	int m_iFrameWidth;
	int m_iFrameHeight;
	int m_iCurrentFrame;
	int m_iTotalFrames;
	float m_fTimeElapsed;
	float m_frameDuration;
	float totalTime;
	bool m_bAnimating;
	bool m_bLooping;

	int m_iStartFrame;
	int m_iEndFrame;

private:

};

#endif // !_ANIMATEDSPRITE_H
