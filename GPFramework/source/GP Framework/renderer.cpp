// COMP710 GP Framework 2022
// This include:
#include "renderer.h"

// Local includes:
#include "texturemanager.h"
#include "logmanager.h"
#include "shader.h"
#include "vertexarray.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "matrix4.h"
#include "texture.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "box2d/box2d.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#include <cassert>
#include <cmath>
#include <iostream>


Renderer::Renderer()
	: m_pTextureManager(0)
	, m_pSpriteShader(0)
	, m_pSpriteVertexData(0)
	, m_glContext(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_fClearRed(0.0f)
	, m_fClearGreen(0.0f)
	, m_fClearBlue(0.0f)
{
}


Renderer::~Renderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	delete m_pSpriteShader;
	m_pSpriteShader = 0;
	delete m_pSpriteVertexData;
	m_pSpriteVertexData = 0;
	delete m_pTextureManager;
	m_pTextureManager = 0;
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}

bool
Renderer::Initialise(bool windowed, int width, int height)
{


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LogSdlError();
		return false;
	}

	if (!windowed)
	{
		//Go fullscreen, with current resolution!
		int numDisplays = SDL_GetNumVideoDisplays();
		SDL_DisplayMode* currentDisplayMode = new SDL_DisplayMode[numDisplays];

		for (int k = 0; k < numDisplays; ++k)
		{
			int result = SDL_GetCurrentDisplayMode(k, &currentDisplayMode[k]);
		}

		//Use the widest display?
		int widest = 0;
		int andItsHeight = 0;

		for (int k = 0; k < numDisplays; ++k)
		{
			if (currentDisplayMode[k].w > widest)
			{
				widest = currentDisplayMode[k].w;
				andItsHeight = currentDisplayMode[k].h;
			}
		}

		delete[] currentDisplayMode;
		currentDisplayMode = 0;

		width = widest;
		height = andItsHeight;
	}

	bool initialised = InitialiseOpenGL(width, height);

	SetFullscreen(!windowed);

	if (initialised)
	{
		m_pTextureManager = new TextureManager();
		assert(m_pTextureManager);
		initialised = m_pTextureManager->Initialise();

	}

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_glContext);
	ImGui_ImplOpenGL3_Init();

	return initialised;
}

bool
Renderer::InitialiseOpenGL(int screenWidth, int screenHeight)
{
	m_iWidth = screenWidth;
	m_iHeight = screenHeight;

	m_pWindow = SDL_CreateWindow("COMP710 GP Framework 2022", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	m_glContext = SDL_GL_CreateContext(m_pWindow);

	GLenum glewResult = glewInit();

	if (glewResult != GLEW_OK)
	{
		return false;
	}

	//Disabled VSYNC
	SDL_GL_SetSwapInterval(0);

	bool shadersLoaded = SetupSpriteShader();

	return shadersLoaded;

}

void 
Renderer::Clear()
{
	glClearColor(m_fClearRed, m_fClearGreen, m_fClearBlue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void 
Renderer::Present()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(m_pWindow);
}

void 
Renderer::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		// SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, 0);
		SDL_SetWindowSize(m_pWindow, m_iWidth, m_iHeight);
	}
	else
	{
		SDL_SetWindowFullscreen(m_pWindow, 0);
	}
}

void 
Renderer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_fClearRed = r / 255.0f;
	m_fClearGreen = g / 255.0f;
	m_fClearBlue = b / 255.0f;
}

void
Renderer::GetClearColour(unsigned char& r, unsigned char& g, unsigned char& b)
{
	r = static_cast<unsigned char>(m_fClearRed * 255.0f);
	g = static_cast<unsigned char>(m_fClearGreen * 255.0f);
	b = static_cast<unsigned char>(m_fClearBlue * 255.0f);
}

int 
Renderer::GetWidth() const
{
	return m_iWidth;
}

int
Renderer::GetHeight() const
{
	return m_iHeight;
}

Sprite*
Renderer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

void
Renderer::LogSdlError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

bool 
Renderer::SetupSpriteShader()
{
	m_pSpriteShader = new Shader();

	bool loaded = m_pSpriteShader->Load("shaders\\sprite.vert", "shaders\\sprite.frag");

	m_pSpriteShader->SetActive();

	float vertices[] =
	{
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // Top Left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top right
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // Bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f // Bottom left
	};

	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	m_pSpriteVertexData = new VertexArray(vertices, 4, indices, 6);

	return loaded;
}

void 
Renderer::DrawSprite(Sprite& sprite)
{
	m_pSpriteShader->SetActive();
	m_pSpriteVertexData->SetActive();

	float angleInDegrees = sprite.GetAngle();

	float sizeX = static_cast<float>(sprite.GetWidth());
	float sizeY = static_cast<float>(sprite.GetHeight());

	const float PI = 3.14159f;
	float angleInRadians = (angleInDegrees * PI) / 180.0f;

	Matrix4 world;
	SetIdentity(world);
	world.m[0][0] = cosf(angleInRadians) * (sizeX);
	world.m[0][1] = -sinf(angleInRadians) * (sizeX);
	world.m[1][0] = sinf(angleInRadians) * (sizeY);
	world.m[1][1] = cosf(angleInRadians) * (sizeY);
	world.m[3][0] = static_cast<float>(sprite.GetX());
	world.m[3][1] = static_cast<float>(sprite.GetY());

	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	Matrix4 orthoViewProj;
	CreateOrthoProjection(orthoViewProj, static_cast<float>(m_iWidth), static_cast<float>(m_iHeight));

	m_pSpriteShader->SetVector4Uniform("colour", sprite.GetRedTint(), sprite.GetGreenTint(), sprite.GetBlueTint(), sprite.GetAlpha());

	m_pSpriteShader->SetMatrixUniform("uViewProj", orthoViewProj);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Carry on from 115
}

AnimatedSprite*
Renderer::CreateAnimatedSprite(const char* pcFileName)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFileName);

	AnimatedSprite* pSprite = new AnimatedSprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("AnimatedSprite failed to create");
	}

	return pSprite;
}

void
Renderer::DrawAnimatedSprite(AnimatedSprite& sprite, int frame)
{
	m_pSpriteShader->SetActive();

	float angleInDegrees = sprite.GetAngle();
	float sizeX = static_cast<float>(sprite.GetWidth());
	float sizeY = static_cast<float>(sprite.GetHeight());

	const float PI = 3.14159f;
	float angleInRadians = (angleInDegrees * PI) / 180.0f;

	Matrix4 world;
	SetIdentity(world);
	world.m[0][0] = cosf(angleInRadians) * (sizeX);
	world.m[0][1] = -sinf(angleInRadians) * (sizeX);
	world.m[1][0] = sinf(angleInRadians) * (sizeY);
	world.m[1][1] = cosf(angleInRadians) * (sizeY);
	world.m[3][0] = static_cast<float>(sprite.GetX());
	world.m[3][1] = static_cast<float>(sprite.GetY());

	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	Matrix4 orhtoViewProj;
	CreateOrthoProjection(orhtoViewProj, static_cast<float>(m_iWidth), static_cast<float>(m_iHeight));

	m_pSpriteShader->SetVector4Uniform("colour", sprite.GetRedTint(), sprite.GetGreenTint(), sprite.GetBlueTint(), sprite.GetAlpha());
	m_pSpriteShader->SetMatrixUniform("uViewProj", orhtoViewProj);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)((frame * 6) * sizeof(GLuint)));

}

void
Renderer::CreateStaticText(const char* pText, int pointsize)
{
	Texture* pTexture = new Texture();
	pTexture->LoadTextTexture(pText, "PROXON", pointsize);
	m_pTextureManager->AddTexture(pText, pTexture);
}

void Renderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

	// Use the same shader as in DrawSprite
	m_pSpriteShader->SetActive();

	// Set up vertex data for the polygon
	GLfloat glverts[16]; // Allow for polygons up to 8 vertices

	// Fill in vertex positions as directed by Box2D
	for (int i = 0; i < vertexCount; i++) {
		glverts[i * 2] = vertices[i].x;
		glverts[i * 2 + 1] = vertices[i].y;
	}

	// Set the transformation matrix to the shader
	Matrix4 world;
	SetIdentity(world);
	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	// Set the orthographic projection (same as in DrawSprite)
	Matrix4 orthoViewProj;
	CreateOrthoProjection(orthoViewProj, static_cast<float>(m_iWidth), static_cast<float>(m_iHeight));
	m_pSpriteShader->SetMatrixUniform("uViewProj", orthoViewProj);

	// Set the color for the solid polygon
	m_pSpriteShader->SetVector4Uniform("colour", color.r, color.g, color.b, 1.0f); // Full opacity

	// Enable blending for smoother visuals
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable the vertex array and set the pointer to our vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, glverts);

	// Draw the solid area as a triangle fan
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	// Draw the outline
	glColor4f(1, 0, 1, 1); // Outline color (e.g., purple)
	glLineWidth(400.0f); // Set line width for the outline to a thicker value
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount); // Draw outline

	// Disable vertex array after drawing
	glDisableClientState(GL_VERTEX_ARRAY);

	// Disable blending after drawing if needed
	glDisable(GL_BLEND);
}


void Renderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	// Use the same shader as in DrawSprite
	m_pSpriteShader->SetActive();

	// Safety check for the vertex count
	if (vertexCount <= 0 || vertices == nullptr) {
		std::cerr << "Error: Invalid vertex count or null vertices." << std::endl;
		return;
	}

	// Create a buffer for the vertices
	GLfloat glverts[8]; // Allow for polygons up to 4 vertices (8 floats for 4 points)

	// Scale the vertices based on your pixel-to-metre conversion
	float sizeMultiplier = 10000000.0f; // Adjust as needed

	// Fill in vertex positions
	for (int i = 0; i < vertexCount; i++) {
		if (i >= 4) {
			std::cerr << "Warning: More vertices than expected, only first 4 will be used." << std::endl;
			break;
		}
		glverts[i * 2] = vertices[i].x * sizeMultiplier;          // X coordinate
		glverts[i * 2 + 1] = vertices[i].y * sizeMultiplier;      // Y coordinate
	}

	// Set up vertex pointer
	glVertexPointer(2, GL_FLOAT, 0, glverts);
	glEnableClientState(GL_VERTEX_ARRAY); // Use vertices in subsequent calls

	// Set the color for the polygon
	m_pSpriteShader->SetVector4Uniform("colour", color.r, color.g, color.b, 1.0f); // Full opacity

	// Set line width
	glLineWidth(2.0f); // Set to desired thickness

	// Draw outline
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount); // Draw outline

	// Disable vertex array after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
}



void Renderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	const int numSegments = 20; // Number of segments to approximate the circle
	GLfloat vertices[40]; // 20 points (x, y) for the circle
	float angleStep = 2.0f * M_PI / numSegments;

	// Calculate circle vertices
	for (int i = 0; i < numSegments; i++) {
		float angle = i * angleStep;
		vertices[i * 2] = center.x + radius * cosf(angle);
		vertices[i * 2 + 1] = center.y + radius * sinf(angle);
	}

	// Use the same shader as in DrawSprite
	m_pSpriteShader->SetActive();

	// Set up vertex array
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY); // Use vertices in subsequent calls

	// Set color for the circle
	m_pSpriteShader->SetVector4Uniform("colour", color.r, color.g, color.b, 1.0f); // Full opacity

	// Set line width for the circle
	glLineWidth(2.0f); // Set to desired thickness

	// Draw circle outline
	glDrawArrays(GL_LINE_LOOP, 0, numSegments); // Draw outline

	// Disable vertex array after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
}


void Renderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	const int numSegments = 20; // Number of segments to approximate the circle
	GLfloat vertices[40]; // 20 points (x, y) for the circle
	float angleStep = 2.0f * M_PI / numSegments;

	// Calculate circle vertices
	for (int i = 0; i < numSegments; i++) {
		float angle = i * angleStep;
		vertices[i * 2] = center.x + radius * cosf(angle);
		vertices[i * 2 + 1] = center.y + radius * sinf(angle);
	}

	// Use the same shader as in DrawSprite
	m_pSpriteShader->SetActive();

	// Set up transformation matrix for the circle
	Matrix4 world;
	SetIdentity(world);
	world.m[3][0] = center.x; // Set circle center X position
	world.m[3][1] = center.y; // Set circle center Y position

	// Set the transformation matrix to the shader
	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	// Set orthographic projection
	Matrix4 orthoViewProj;
	CreateOrthoProjection(orthoViewProj, static_cast<float>(m_iWidth), static_cast<float>(m_iHeight));
	m_pSpriteShader->SetMatrixUniform("uViewProj", orthoViewProj);

	// Set the color for the solid circle
	m_pSpriteShader->SetVector4Uniform("colour", color.r, color.g, color.b, 1.0f); // Full opacity

	// Enable blending for smoother visuals
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable vertex array and draw the solid circle
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY); // Use vertices in subsequent calls

	// Draw solid circle
	glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments);

	// Draw the outline
	glLineWidth(2.0f); // Set to desired thickness (adjust as necessary)
	glColor4f(1, 0, 1, 1); // Outline color (purple)
	glDrawArrays(GL_LINE_LOOP, 0, numSegments); // Draw outline

	// Disable vertex array after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND); // Optional: Disable blending after drawing
}


void Renderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	// Set up vertex array for the line segment
	GLfloat vertices[4]; // Two points (x, y) for the line
	vertices[0] = p1.x; vertices[1] = p1.y; // First point
	vertices[2] = p2.x; vertices[3] = p2.y; // Second point

	// Use the same shader as in DrawSprite
	m_pSpriteShader->SetActive();

	// Set up transformation matrix for the line segment
	Matrix4 world;
	SetIdentity(world);

	// Calculate midpoint for positioning
	float midX = (p1.x + p2.x) / 2.0f;
	float midY = (p1.y + p2.y) / 2.0f;

	// Set the position of the midpoint
	world.m[3][0] = midX; // Set midpoint X position
	world.m[3][1] = midY; // Set midpoint Y position

	// Set the transformation matrix to the shader
	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	// Set orthographic projection
	Matrix4 orthoViewProj;
	CreateOrthoProjection(orthoViewProj, static_cast<float>(m_iWidth), static_cast<float>(m_iHeight));
	m_pSpriteShader->SetMatrixUniform("uViewProj", orthoViewProj);

	// Set the color for the line
	m_pSpriteShader->SetVector4Uniform("colour", color.r, color.g, color.b, 1.0f); // Full opacity

	// Enable blending for smoother visuals
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable vertex array and draw the line segment
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY); // Use vertices in subsequent calls
	glLineWidth(2.0f); // Set to desired thickness (adjust as necessary)

	// Draw line segment
	glDrawArrays(GL_LINES, 0, 2);

	// Disable vertex array after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND); // Optional: Disable blending after drawing
}


void Renderer::DrawTransform(const b2Transform& xf)
{
	const float lineLength = 0.5f; // Length of transformation lines
	b2Vec2 p1 = xf.p;

	// X-axis
	b2Vec2 p2_x = p1 + lineLength * xf.q.GetXAxis(); // Endpoint for X-axis

	// Set up vertex array for X-axis
	GLfloat vertices_x[4]; // Two points (x, y)
	vertices_x[0] = p1.x; vertices_x[1] = p1.y; // Start point
	vertices_x[2] = p2_x.x; vertices_x[3] = p2_x.y; // End point

	// Use the same shader as in DrawSprite
	m_pSpriteShader->SetActive();

	// Set up transformation matrix for the X-axis line
	Matrix4 world;
	SetIdentity(world);
	// Calculate the midpoint for positioning
	float midX = (p1.x + p2_x.x) / 2.0f;
	float midY = (p1.y + p2_x.y) / 2.0f;
	world.m[3][0] = midX; // Set midpoint X position
	world.m[3][1] = midY; // Set midpoint Y position

	// Set the transformation matrix to the shader
	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	// Set orthographic projection
	Matrix4 orthoViewProj;
	CreateOrthoProjection(orthoViewProj, static_cast<float>(m_iWidth), static_cast<float>(m_iHeight));
	m_pSpriteShader->SetMatrixUniform("uViewProj", orthoViewProj);

	// Set color for the X-axis (Red)
	m_pSpriteShader->SetVector4Uniform("colour", 1.0f, 0.0f, 0.0f, 1.0f); // Full opacity

	// Draw the line segment for the X-axis
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glVertexPointer(2, GL_FLOAT, 0, vertices_x);
	glDrawArrays(GL_LINES, 0, 2); // Draw X-axis line

	// Y-axis
	b2Vec2 p2_y = p1 + lineLength * xf.q.GetYAxis(); // Endpoint for Y-axis

	// Set up vertex array for Y-axis
	GLfloat vertices_y[4]; // Two points (x, y)
	vertices_y[0] = p1.x; vertices_y[1] = p1.y; // Start point
	vertices_y[2] = p2_y.x; vertices_y[3] = p2_y.y; // End point

	// Set the transformation matrix to the shader for the Y-axis
	// Reuse world matrix and set the midpoint for Y-axis
	midX = (p1.x + p2_y.x) / 2.0f;
	midY = (p1.y + p2_y.y) / 2.0f;
	world.m[3][0] = midX; // Set midpoint X position
	world.m[3][1] = midY; // Set midpoint Y position;

	// Set the transformation matrix to the shader
	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	// Set color for the Y-axis (Green)
	m_pSpriteShader->SetVector4Uniform("colour", 0.0f, 1.0f, 0.0f, 1.0f); // Full opacity

	// Draw the line segment for the Y-axis
	glVertexPointer(2, GL_FLOAT, 0, vertices_y);
	glDrawArrays(GL_LINES, 0, 2); // Draw Y-axis line

	// Disable blending after drawing if needed
	glDisable(GL_BLEND);
}


void Renderer::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	// Use the same shader as in DrawSprite (assuming it works for points as well)
	m_pSpriteShader->SetActive();

	// Set up the point as a "sprite-like" object
	Matrix4 world;
	SetIdentity(world);

	// Apply size as scaling to the point
	world.m[0][0] = size;  // Scale in X
	world.m[1][1] = size;  // Scale in Y

	// Set the position of the point
	world.m[3][0] = p.x; // X position
	world.m[3][1] = p.y; // Y position

	// Set the transformation matrix to the shader
	m_pSpriteShader->SetMatrixUniform("uWorldTransform", world);

	// Set the orthographic projection (same as in DrawSprite)
	Matrix4 orthoViewProj;
	CreateOrthoProjection(orthoViewProj, static_cast<float>(m_iWidth), static_cast<float>(m_iHeight));
	m_pSpriteShader->SetMatrixUniform("uViewProj", orthoViewProj);

	// Set the color for the point
	m_pSpriteShader->SetVector4Uniform("colour", color.r, color.g, color.b, 1.0f);  // Full opacity

	// Enable blending for smoother visuals
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the point as a small quad or triangle (since OpenGL doesn't directly support large points)
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Optional: Disable blending after drawing if needed
	glDisable(GL_BLEND);
}
