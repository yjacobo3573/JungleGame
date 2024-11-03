#include "JumpComponent.h"
#include "GameObject.h"
#include "BodyComponent.h"

void JumpComponent::update()
{
	auto body = parent().get<BodyComponent>();

	if (Input::isKeyDown(SDLK_UP))
	{


    int velocityY= body->getVelocityY();



    body->getY() -= velocityY;

    }


	if (Input::isKeyDown(SDLK_DOWN))
	{
     int velocityY= body->getVelocityY();

     body->getY() += velocityY;

    }
}

void JumpComponent::draw()
{


}
