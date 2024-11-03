#include "Input.h"



// Initialize static members
std::set<SDL_Keycode> Input::keysDown;
std::set<Uint8> Input::mouseButtonsDown;
std::pair<int, int> Input::mousePosition = { 0, 0 };





void Input::processEvent(const SDL_Event& event)
{
    switch (event.type) {
    case SDL_KEYDOWN:
        keysDown.insert(event.key.keysym.sym);
        break;

    case SDL_KEYUP:
        keysDown.erase(event.key.keysym.sym);
        break;

    case SDL_MOUSEBUTTONDOWN:
        mouseButtonsDown.insert(event.button.button);
        break;

    case SDL_MOUSEBUTTONUP:
        mouseButtonsDown.erase(event.button.button);
        break;

    case SDL_MOUSEMOTION:
        mousePosition = { event.motion.x, event.motion.y };
        break;
    }
}

bool Input::isKeyDown(SDL_Keycode key)
{
    return keysDown.find(key) != keysDown.end();
}

bool Input::isMouseButtonDown(Uint8 button)
{
    return mouseButtonsDown.find(button) != mouseButtonsDown.end();
}

std::pair<int, int> Input::getMousePosition()
{
	return mousePosition;
}
