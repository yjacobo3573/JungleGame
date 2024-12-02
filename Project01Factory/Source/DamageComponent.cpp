#include "DamageComponent.h"
#include<iostream>
#include "BodyComponent.h"
#include "GameObject.h"

void DamageComponent::draw()
{
}

void DamageComponent::update()
{
}

void DamageComponent::drawDebugShape()
{
}

void DamageComponent::collisionCounter()
{
	if (isAlive==true) {

collisions++;

if (collisions >= 3) {
    isAlive=false;
	//kill(); //remove the player end the game
}


}
}

void DamageComponent::kill()
{
	std::cout << "Player has been killed!" << std::endl;
	isAlive = false; // Mark the player as dead

	auto body = parent().get<BodyComponent>();

	if (body)
	{
		body->getBody()->GetWorld()->DestroyBody(body->getBody());
    }
}

bool DamageComponent::getIsAlive()
{
	return isAlive;
}
