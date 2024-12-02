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

void BodyComponent::drawDebugShape()
{
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







float BodyComponent::getX() const
{
	return _x ;
}

float BodyComponent::getY() const
{
	return _y ;
}

float BodyComponent::getAngle() const
{
	// TODO: insert retur
return _angle;
}

float BodyComponent::getVelocityX() const
{
	// TODO: insert return statement here
return _velocityX;
}

float BodyComponent::getVelocityY() const
{
	// TODO: insert return statement here
return _velocityY;
}

float BodyComponent::getWidth() const
{
	// TODO: insert return statement here
return _width;
}

float BodyComponent::getHeight() const
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

void BodyComponent::setX(float x)
{

  _x=x;

}

void BodyComponent::setY(float y)
{
_y=y;
}

void BodyComponent::setAngle(float angle)
{

_angle=angle;
}

void BodyComponent::setVelocityX(float velocityX)
{
_velocityX=velocityX;
}

void BodyComponent::setVelocityY(float velocityY)
{
_velocityY=velocityY;
}
