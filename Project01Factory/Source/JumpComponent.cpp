#include "JumpComponent.h"
#include "GameObject.h"
#include "BodyComponent.h"

void JumpComponent::drawDebugShape()
{
}

void JumpComponent::update()
{
	auto body = parent().get<BodyComponent>();

	if (Input::isKeyDown(SDLK_UP))
	{

   if(body){

   float jumpForce= -10.0f;
   body->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.0f, jumpForce), true);
      }
    }


	if (Input::isKeyDown(SDLK_DOWN))
	{

    if(body){
     int velocityY= body->getVelocityY();

     body->setY(body->getY() + velocityY);
      }
    }
}

void JumpComponent::draw()
{


}
