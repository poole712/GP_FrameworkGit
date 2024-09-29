#pragma once
#ifndef _SCENE_H
#define _SCENE_H

class Renderer;
class InputSystem;

class Scene {
public: 
	Scene();
	virtual ~Scene();

	virtual bool Initialise(Renderer& renderer) = 0;
	virtual void Process(float deltaTime, InputSystem& inputSystem, int& scene) = 0;
	virtual void Draw(Renderer& renderer) = 0;
	virtual void DebugDraw() = 0;

protected:

private:
	Scene(const Scene& scene);
	Scene& operator=(const Scene& scene);

public:

protected:

private:

};

#endif // !_SCENE_H
