#ifndef  _BALL_H
#define _BALL_H

#include "vector2.h"

class Renderer;
class Sprite;

class Ball
{
public:
	Ball();
	~Ball();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void DebugDraw();
	void RandomiseColour();
	void RandomiseSize();

	Vector2& Position();

protected:
	void ComputeBounds(int width, int height);

private:
	Ball(const Ball& ball);
	Ball& operator=(const Ball& ball);

public:

protected:
	Vector2 m_position;
	Vector2 m_velocity;

	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;

	Sprite* m_pSprite;
	bool m_bAlive;

	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;
};

#endif // ! _BALL_H
