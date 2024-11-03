#ifndef   INPUT_H
#define   INPUT_H
#include <SDL2/SDL.h>
#include <unordered_map>
#include <set>
#include <utility>  // for std::pair


class Input
{
public:
    // Update the input state based on SDL events (static method)
    static void processEvent(const SDL_Event& event);

    // Check if a specific key is currently down (static method)
    static bool isKeyDown(SDL_Keycode key);


    // Check if a specific mouse button is currently down (static method)
    static bool isMouseButtonDown(Uint8 button);


    // Get the current mouse position (static method)
    static std::pair<int, int> getMousePosition();

   private:
       static std::set<SDL_Keycode> keysDown;               // Track which keys are down (static)
       static std::set<Uint8> mouseButtonsDown;             // Track which mouse buttons are down (static)
       static std::pair<int, int> mousePosition;            // Store the current mouse position (static)




};

#endif