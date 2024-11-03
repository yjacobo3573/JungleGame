#include "SuperSpeedComponent.h"
#include "GameObject.h"
#include "BodyComponent.h"

void SuperSpeedComponent::update()
{
	auto body = parent().get<BodyComponent>();

	if (Input::isKeyDown(SDLK_s))
	{

  int velocityX= body->getVelocityX()*10;
  body->getX() += velocityX;

    }
}

void SuperSpeedComponent::draw()
{
}
