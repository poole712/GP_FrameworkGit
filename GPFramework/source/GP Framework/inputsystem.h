#ifndef _INPUTSYSTEM_H
#define _INPUTSYSTEM_H

#include "vector2.h"

#include <SDL.h>

class XboxController;

enum ButtonState
{
	BS_NEAUTRAL,
	BS_PRESSED,
	BS_RELEASED,
	BS_HELD
};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	bool Initialise();
	void ProcessInput();

	ButtonState GetKeyState(SDL_Scancode key);

	const Vector2& GetMousePosition() const;
	const Vector2& GetMouseScrollWheel() const;
	ButtonState GetMouseButtonState(int button);
	void ShowMouseCursor(bool show);
	void SetRelativeMode(bool relative);

	int GetNumberOfControllersAttached() const;
	XboxController* GetController(int controllerIndex);

protected:
	void ProcessMouseWheel(SDL_Event& event);

private:
	InputSystem(const InputSystem& inputsystem);
	InputSystem& operator=(const InputSystem& inputsystem);

public:

protected:
	unsigned char m_previousKeyboardState[SDL_NUM_SCANCODES];
	const unsigned char* m_pCurrentKeyboardState;

	Vector2 m_mousePosition;
	Vector2 m_mouseWheel;
	unsigned int m_previousMouseButtons;
	unsigned int m_currentMouseButtons;
	bool m_bRelativeMouseMode;

	XboxController* m_pXboxController;
	int m_iNumAttachedControllers;


};

#endif // !_INPUTSYSTEM_H
