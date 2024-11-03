#include "ControllerComponent.h"
#include "GameObject.h"
#include "BodyComponent.h"

void ControllerComponent::update()
{

auto body= parent().get<BodyComponent>();

if (Input::isKeyDown(SDLK_RIGHT))
{
	int Velocityx= body->getVelocityX();

   body->getX() += Velocityx;
}

if (Input::isKeyDown(SDLK_LEFT))
{
	int Velocityx = body->getVelocityX();

	body->getX() -= Velocityx;
}



}

void ControllerComponent::draw()
{
}
