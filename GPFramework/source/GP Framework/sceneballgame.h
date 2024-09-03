#ifndef _SCENEBALLGAME_H
#define _SCENEBALLGAME_H

#include "scene.h"

#include <vector>

class Renderer;
class Ball;

class SceneBallGame : public Scene
{
public:
	SceneBallGame();
	virtual ~SceneBallGame();

	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

	void SetAsPlayer();
	void SetGood();
	void SetBad();
	void Shrink();
	void Enlarge();
	float GetRadius();
	void Kill();
	bool IsAlive() const;

protected:
	void SpawnGoodBalls(int number);
	void SpawnBadBalls(int number);
	
	void CheckCollisions();
	bool BallVsBall(Ball* p1, Ball* p2);

private:
	SceneBallGame(const SceneBallGame& sceneballgame);
	SceneBallGame& operator=(const SceneBallGame& sceneballgame);

public:

protected:
	Renderer* m_pRenderer;

	std::vector<Ball*> m_pGoodBalls;
	std::vector<Ball*> m_pBadBalls;

	Ball* m_pPlayerBall;

private:

};

#endif // !_SCENEBALLGAME_H
