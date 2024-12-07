#include "ControllerComponent.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include <Box2D/Box2D.h>

void ControllerComponent::update()
{

auto body= parent().get<BodyComponent>();

if (Input::isKeyDown(SDLK_RIGHT))
{

   if(body){


    auto velocityX= body->getVelocityX();

	body->getBody()->SetLinearVelocity(b2Vec2(velocityX, 0.0f));

    auto linearDamping= body->getLinearDamping();
    
    body->getBody()->SetLinearDamping(linearDamping);

   Engine::stepsSound();
   }

 //body->setX(body->getX() + Velocityx);
}

if (Input::isKeyDown(SDLK_LEFT))
{
   if(body){
    auto velocityX = body->getVelocityX();

    body->getBody()->SetLinearVelocity(b2Vec2(-velocityX, 0.0f));

    auto linearDamping = body->getLinearDamping();

    body->getBody()->SetLinearDamping(linearDamping);
  }
    
}



}

void ControllerComponent::draw()
{
}

void ControllerComponent::drawDebugShape()
{
}
