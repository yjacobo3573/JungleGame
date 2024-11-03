#ifndef   JUMPCOMPONENT_H
#define   JUMPCOMPONENT_H
#include "Component.h"
#include "Input.h"


class JumpComponent: public Component
{
public:

	JumpComponent(GameObject& owner) : Component(owner) {}



	void update() override;
	void draw() override;
};

#endif