#include "SuperSpeedComponent.h"
#include "GameObject.h"
#include "BodyComponent.h"

void SuperSpeedComponent::update()
{
	auto body = parent().get<BodyComponent>();

	if (Input::isKeyDown(SDLK_s))
	{
   
    auto velocityX= body->getVelocityX()*9;
    body->getBody()->SetLinearVelocity(b2Vec2(velocityX, 0.0f));

     auto linearDamping= body->getLinearDamping();
     body->getBody()->SetLinearDamping(linearDamping);

    }
}

void SuperSpeedComponent::draw()
{
}
