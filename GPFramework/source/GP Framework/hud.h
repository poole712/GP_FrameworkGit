#ifndef  _HUD_H
#define _HUD_H

class Renderer;
class Sprite;
class InputSystem;
class UiHandler;
class Game;

class Hud
{
public:
	Hud();
	~Hud();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem, Game& game);
	void Draw(Renderer& renderer);

protected:

private:
	Hud(const Hud& hud);
	Hud& operator=(const Hud& hud);

public:

protected:
	Sprite* m_pFireControls;
	Sprite* m_pEarthControls;
	Sprite* m_pIceControls;


};
#endif
