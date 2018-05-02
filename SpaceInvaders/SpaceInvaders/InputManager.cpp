#include "InputManager.h"

InputManager * InputManager::instance = NULL;

InputManager * InputManager::getInstance() {
	if (!instance)
		instance = new InputManager();

	return instance;
}

void InputManager::Release() {
	delete instance;
	instance = NULL;
}

InputManager::InputManager() {
	keyboardState = SDL_GetKeyboardState(&keyCount);
	oldKeyboardState = std::unique_ptr<Uint8[]>(new Uint8[keyCount]);
}


InputManager::~InputManager() {
}

void InputManager::Update() {
	memcpy(oldKeyboardState.get(), keyboardState, keyCount * sizeof(Uint8));
	SDL_PumpEvents();
}

bool InputManager::KeyDown(SDL_Scancode scanCode) {
	return ((keyboardState[scanCode]) && (!oldKeyboardState[scanCode]));
}

bool InputManager::KeyStillDown(SDL_Scancode scanCode) {
	return ((keyboardState[scanCode]) && (oldKeyboardState[scanCode]));
}

bool InputManager::KeyUp(SDL_Scancode scanCode) {
	return ((!keyboardState[scanCode]) && (oldKeyboardState[scanCode]));
}

bool InputManager::KeyStillUp(SDL_Scancode scanCode) {
	return ((!keyboardState[scanCode]) && (!oldKeyboardState[scanCode]));
}
