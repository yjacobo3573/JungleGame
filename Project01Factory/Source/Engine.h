#ifndef ENGINE_H
#define ENGINE_H

#include "ComponentFactory.h"
#include "BodyComponent.h"

#include<SDL2/SDL.h>

#include<vector>

#include<string>

#include "Input.h"

#include"GameObject.h"

#include "View.h"

#include <Box2D/Box2D.h>
#include <SDL2/SDL_mixer.h>

#include "Component.h"

class ComponentFactory;

class Engine {

	//members
     public: 
      static View view; 
      static constexpr int targetFPS= 60;

      static constexpr float frameDuration= 1000.0f/targetFPS; 
//in milliseconds which is 16.67
      static const float SCALE; //1 meter in physics=100 pixels in rendering

      static float deltaTime;

      int width;

    

	  std::unique_ptr < ComponentFactory > compoLibrary;
      std::unique_ptr<BodyComponent> bodyComponent;

	  Engine();

	  int loadLevel();

      int loadLevel2();

      static void thumpSound();

      static void stepsSound();

      //delete level 1 game objects
      void deleteGameObjects();

     //delete level 1 Box2d bodies
	  void destroyAllBodies();

	  // Initialize the Engine 
	  bool init(const char* title, int width, int height);

	  //Handle events 
	  void handleEvents();

	  // Update all game objects 
	  void update();

	  // Render all game objects 
	  void render();

	  // Clean up SDL resources 
	  void clean();

	  // Check if the engine is still running 
	  bool running();

	  // Add a GameObject to the engine 
	 static void addGameObject(std::unique_ptr < GameObject > gameObject);

	  //Run the engine(static)
	  void run();

	  static SDL_Renderer* getRenderer();

	
//Create a Box2D body
	  b2Body* CreateBox(b2World& world, float x, float y, float width, float height, bool isDynamic, float density, float friction, float linearDamping);
	  b2Body* CreatePlayerBody(b2World& world, float x, float y, float width, float height, bool isDynamic, float density, float friction, float linearDamping, bool includeHead);

//Box2d world
	  void physicsWorld();
      void physicsWorldLevel2();

    void checkCollisions();

    void handleCollisions(GameObject* player, GameObject* enemy);

//screen dimensions
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;

    //void endGame(GameObject* gameObject);
	static std::vector<std::unique_ptr<GameObject>> toAdd;

	static std::vector < std::unique_ptr < GameObject >> gameObjects; // Track game objects

private:
       bool isRunning; // Engine running state 

	   SDL_Window* window; // SDL window 
	   static SDL_Renderer* renderer; // SDL renderer (static)
     
	   b2World world;
      
	 static Mix_Chunk* thumpSoundEffect;
     static Mix_Chunk* footStepsSound;
	 
       
};

#endif