#ifndef   AICOMPONENTPATROLING_H
#define   AICOMPONENTPATROLING_H
#include "Component.h"
#include "Input.h"
#include "Engine.h"
class AIComponentPatroling: public Component
{
public:
	AIComponentPatroling(GameObject& owner) : Component(owner) {}

	void draw() override;


	void update() override;

	void drawDebugShape() override;



};




#endif