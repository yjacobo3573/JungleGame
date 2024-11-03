#ifndef   ENGINE_H
#define   ENGINE_H
#include "ComponentFactory.h"
#include<SDL2/SDL.h>
#include<vector>
#include<string>
#include "Input.h"
#include"GameObject.h"

class ComponentFactory;

class Engine {

	//members
   public:
	 int width;
    
  std::unique_ptr<ComponentFactory> compoLibrary;

     Engine();

   int loadLevel();
    
// Initialize the Engine (static)
   bool init(const char* title, int width, int height);

    //Handle events (static)
     void handleEvents();

    // Update all game objects (static)
    void update();

    // Render all game objects (static)
   void render();

    // Clean up SDL resources (static)
    void clean();

    // Check if the engine is still running (static)
     bool running();

    // Add a GameObject to the engine (static)
     void addGameObject(std::unique_ptr<GameObject> gameObject);

    //Run the engine(static)
   void run();
    
    static SDL_Renderer* getRenderer();
private:
    bool isRunning;                               // Engine running state (static)
     SDL_Window* window;                           // SDL window (static)
   static SDL_Renderer* renderer;                       // SDL renderer (static)
     std::vector<std::unique_ptr<GameObject>> gameObjects;  // Track game objects
};


#endif