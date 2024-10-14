#ifndef _BACKGROUND_H
#define _BACKGROUND_H

class Sprite;
class Renderer;

class Background
{
public:
	Background();
	~Background();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void CreateForeground();
	void CreateMiddleground();
	void CreateBackground();

	void ProcessForeground(float multiplier);
	void ProcessMiddleground(float multiplier);
	void ProcessBackground(float multiplier);

	void DrawForeground();
	void DrawMiddleground();
	void DrawBackground();

private:
	int m_iWidth;
	int m_iHeight;

	Renderer* m_rRenderer;

	float m_fSpeed;

	Sprite* m_sForeground1;
	Sprite* m_sForeground2;

	Sprite* m_sMiddleground1;
	Sprite* m_sMiddleground2;

	Sprite* m_sBackground1;
	Sprite* m_sBackground2;
};

#endif // _BACKGROUND_H