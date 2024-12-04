#include "spawnComponent.h"

void spawnComponent::update()
{	
	if (Input::isKeyDown(SDLK_SPACE)) {
		
   std::unique_ptr < GameObject > bees = std::make_unique < GameObject >("Bee");
       //create and add a Body component
	  // Create and add a BodyComponent
   auto bodyComponent = std::make_unique<BodyComponent>(*bees,585.0f, 250.0f,0.0f,0.0f,0.0f, 50.0f,50.0f,0.0f,0.0f,false, 0.0f);

   bees->add(std::move(bodyComponent));

   auto spriteComponent= std::make_unique<SpriteComponent>(*bees,"Bee");

   bees->add(std::move(spriteComponent));

   Engine::addGameObject(std::move(bees));

	}
}

void spawnComponent::draw()
{
}

void spawnComponent::drawDebugShape()
{
}
