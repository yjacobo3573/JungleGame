#include "spawnComponent.h"

void spawnComponent::update()
{	
	if (Input::isKeyDown(SDLK_SPACE)) {
		
   std::unique_ptr < GameObject > bees = std::make_unique < GameObject >("Bee");
       //create and add a Body component
	  // Create and add a BodyComponent
   float x= (rand() % (900 - 500 + 1)) + 500; // Random number formula
   float y= (rand()%(20-340+1))+20;
   auto bodyComponent = std::make_unique<BodyComponent>(*bees,x, y, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 0.0f, 0.0f, false, 0.0f);

   bees->add(std::move(bodyComponent));

   auto spriteComponent= std::make_unique<SpriteComponent>(*bees,"Bee");

   bees->add(std::move(spriteComponent));

   Engine::toAdd.push_back(std::move(bees));

	}
}

void spawnComponent::draw()
{
}

void spawnComponent::drawDebugShape()
{
}
