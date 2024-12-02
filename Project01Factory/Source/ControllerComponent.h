#ifndef   CONTROLLERCOMPONENT_H
#define   CONTROLLERCOMPONENT_H
#include "Component.h"
#include "Input.h"

class ControllerComponent: public Component
{

public:

	ControllerComponent(GameObject& owner): Component(owner)  {}



	void update() override;
	void draw() override;


	void drawDebugShape() override;


};





#endif