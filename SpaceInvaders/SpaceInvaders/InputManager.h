#pragma once
#include <SDL.h>
#include <memory>

class InputManager {
public:
	static InputManager* getInstance();
	static void Release();

	void Update();

	// Keyboard
	bool KeyDown(SDL_Scancode scanCode);
	bool KeyStillDown(SDL_Scancode scanCode);
	bool KeyUp(SDL_Scancode scanCode);
	bool KeyStillUp(SDL_Scancode scanCode);

protected:
	const Uint8* keyboardState;
	std::unique_ptr<Uint8[]> oldKeyboardState;
	int keyCount;

private:
	static InputManager* instance;

	InputManager();
	~InputManager();
};

