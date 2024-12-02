#ifndef   SPRITECOMPONENT_H
#define   SPRITECOMPONENT_H
#include "Component.h"
#include "Textures.h"
#include"GameObject.h"
#include "BodyComponent.h"
#include "Engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>



//Manages graphical functionality.
class SpriteComponent : public Component
{

public:
	SpriteComponent(GameObject& parent, std::string textureKey)
		:Component(parent), texture(nullptr){
        
        texture= Textures::get(textureKey);
        
        if (!texture)
        {
      SDL_Log("Failed to load texture for key: %s", textureKey.c_str());
        }
    }



  void update() override;
  void draw() override;

  void drawDebugShape() override;
 

private:
	SDL_Texture* texture;
};





#endif