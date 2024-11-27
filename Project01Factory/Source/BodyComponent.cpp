#include "BodyComponent.h"
#include "Engine.h"




void BodyComponent::draw()
{

this->parent();


}

void BodyComponent::update()
{
//synchronize physics and rendering: Update the BodyComponent::update()
//method to synchronize the Box2D body with its properties

	if (_body) {

    _x= _body->GetPosition().x*Engine::SCALE;
    _y= _body->GetPosition().y*Engine::SCALE;
    
    }

	/*else {
		std::cerr<<"BodyComponent update failed: _body is null."<<std::endl;
	}*/
}

void BodyComponent::setBody(b2Body* body)
{

	if (!body) {
		std::cerr<<"Attempted to set a null b2Body!" << std::endl;
        return;
     }
    _body=body;
}

b2Body* BodyComponent::getBody() const
{
	return _body;
}






//scaling for getting the position in pixels to render
//in sprite component
double BodyComponent::getX() const
{
	return _x ;
}

double BodyComponent::getY() const
{
	return _y ;
}

double BodyComponent::getAngle() const
{
	// TODO: insert retur
return _angle;
}

double BodyComponent::getVelocityX() const
{
	// TODO: insert return statement here
return _velocityX;
}

double BodyComponent::getVelocityY() const
{
	// TODO: insert return statement here
return _velocityY;
}

int BodyComponent::getWidth() const
{
	// TODO: insert return statement here
return _width;
}

int BodyComponent::getHeight() const
{
	// TODO: insert return statement here
return _height;
}

float BodyComponent::getDensity() const
{
	// TODO: insert return statement here
return _density;
}

float BodyComponent::getFriction() const
{
	// TODO: insert return statement here
return _friction;
}

bool BodyComponent::getisDynamic() const
{
	// TODO: insert return statement here
return _isDynamic;
}

float BodyComponent::getLinearDamping() const
{
	// TODO: insert return statement here
return _linearDamping;
}

void BodyComponent::setX(double x)
{

  _x=x;

}

void BodyComponent::setY(double y)
{
_y=y;
}

void BodyComponent::setAngle(double angle)
{

_angle=angle;
}

void BodyComponent::setVelocityX(double velocityX)
{
_velocityX=velocityX;
}

void BodyComponent::setVelocityY(double velocityY)
{
_velocityY=velocityY;
}
