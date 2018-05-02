#include "InputManager.h"

// Singleton
InputManager * InputManager::instance = NULL;

InputManager * InputManager::getInstance() {
	if (!instance)
		instance = new InputManager();

	return instance;
}

// Release singleton
void InputManager::Release() {
	delete instance;
	instance = NULL;
}

// Constructor
InputManager::InputManager() {
	keyboardState = SDL_GetKeyboardState(&keyCount);
	oldKeyboardState = std::unique_ptr<Uint8[]>(new Uint8[keyCount]);
}

// Deconstructor
InputManager::~InputManager() {
}

// Updates the keyboard state
void InputManager::Update() {
	memcpy(oldKeyboardState.get(), keyboardState, keyCount * sizeof(Uint8));
	SDL_PumpEvents();
}

// Compare for key down
bool InputManager::KeyDown(SDL_Scancode scanCode) {
	return ((keyboardState[scanCode]) && (!oldKeyboardState[scanCode]));
}

// Compare for key still down
bool InputManager::KeyStillDown(SDL_Scancode scanCode) {
	return ((keyboardState[scanCode]) && (oldKeyboardState[scanCode]));
}

// Compare for key up
bool InputManager::KeyUp(SDL_Scancode scanCode) {
	return ((!keyboardState[scanCode]) && (oldKeyboardState[scanCode]));
}

// Compare for key still up
bool InputManager::KeyStillUp(SDL_Scancode scanCode) {
	return ((!keyboardState[scanCode]) && (!oldKeyboardState[scanCode]));
}
