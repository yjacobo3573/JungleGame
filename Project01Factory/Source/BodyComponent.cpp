#include "BodyComponent.h"





void BodyComponent::draw()
{

this->parent();


}

void BodyComponent::update()
{

}

double& BodyComponent::getX()
{
	return _x;
}

double& BodyComponent::getY()
{
	return _y;
}

double& BodyComponent::getAngle()
{
	// TODO: insert retur
return _angle;
}

double& BodyComponent::getVelocityX()
{
	// TODO: insert return statement here
return _velocityX;
}

double& BodyComponent::getVelocityY()
{
	// TODO: insert return statement here
return _velocityY;
}

int& BodyComponent::getWidth()
{
	// TODO: insert return statement here
return _width;
}

int& BodyComponent::getHeight()
{
	// TODO: insert return statement here
return _height;
}
