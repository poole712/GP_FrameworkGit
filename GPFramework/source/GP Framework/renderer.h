#ifndef _RENDERER_H
#define _RENDERER_H

//Forward Declarations:
class TextureManager;
class Shader;
class VertexArray;
class Sprite;
class AnimatedSprite;
struct SDL_Window;

// Library includes
#include <SDL.h>
#include "box2d/box2d.h"


class Renderer
{
	//Member methods:
public:
	Renderer();
	~Renderer();

	bool Initialise(bool windowed, int width = 0, int height = 0);

	void Clear();
	void Present();

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);
	void GetClearColour(unsigned char& r, unsigned char& g, unsigned char& b);

	int GetWidth() const;
	int GetHeight() const;

	Sprite* CreateSprite(const char* pcFilename);
	AnimatedSprite* CreateAnimatedSprite(const char* pcFilename);
	void DrawSprite(Sprite& sprite);
	void DrawAnimatedSprite(AnimatedSprite& sprite, int frame);
	void CreateStaticText(const char* pText, int pointsize);

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color);




protected:
	bool InitialiseOpenGL(int screenWidth, int screenHeight);
	void SetFullscreen(bool fullscreen);

	void LogSdlError();

	bool SetupSpriteShader();

private:
	Renderer(const Renderer& renderer);
	Renderer& operator=(const Renderer& renderer);

	//Member data:
public:

protected:
	TextureManager* m_pTextureManager;
	SDL_Window* m_pWindow;
	SDL_GLContext m_glContext;

	Shader* m_pSpriteShader;
	VertexArray* m_pSpriteVertexData;

	int m_iWidth;
	int m_iHeight;

	float m_fClearRed;
	float m_fClearGreen;
	float m_fClearBlue;

private:

};

#endif // !_RENDERER_H
