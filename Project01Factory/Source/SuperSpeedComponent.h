#ifndef   SUPERSPEEDCOMPONENT_H
#define   SUPERSPEEDCOMPONENT_H
#include "Component.h"
#include "Input.h"

class SuperSpeedComponent : public Component {
	public:

		SuperSpeedComponent(GameObject & owner) : Component(owner) {}



		void update() override;
		void draw() override;

		void drawDebugShape() override;

};





#endif
