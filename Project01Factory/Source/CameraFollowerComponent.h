#ifndef   CAMERAFOLLOWERCAMERA_H
#define   CAMERAFOLLOWERCAMERA_H
#include  "Component.h"
#include  "View.h"
#include   "BodyComponent.h"
#include<algorithm>
//Manages the camera following of the player

class CameraFollowerComponent : public Component
{

public:

	CameraFollowerComponent(GameObject& owner) : Component(owner) {}

	void draw() override;


	void update() override;





};

#endif
