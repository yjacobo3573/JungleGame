#include "JumpComponent.h"
#include "GameObject.h"
#include "BodyComponent.h"

void JumpComponent::update()
{
	auto body = parent().get<BodyComponent>();

	if (Input::isKeyDown(SDLK_UP))
	{


    auto velocityY= body->getVelocityY();
    body->getBody()->SetLinearVelocity(b2Vec2(0.0f, velocityY));

    }


	if (Input::isKeyDown(SDLK_DOWN))
	{
     int velocityY= body->getVelocityY();

     body->setY(body->getY() + velocityY);

    }
}

void JumpComponent::draw()
{


}
