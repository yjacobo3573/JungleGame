#ifndef   BODYCOMPONENT_H
#define   BODYCOMPONENT_H
#include <Box2D/Box2D.h>

#include "Component.h"

//Manages basic physics (position, angle, velocity).


class BodyComponent: public Component
{
public:

BodyComponent(GameObject& owner, float x, float y, float angle, float velocityX, float velocityY, float width, float height, float density, float friction, bool isDynamic, float linearDamping )
    : Component(owner),_x(x), _y(y), _angle(angle), _velocityX(velocityX), _velocityY(velocityY), _width(width), _height(height), _density(density), _friction(friction), _isDynamic(isDynamic), _linearDamping(linearDamping) {}


BodyComponent()=default;

float getX() const;
float getY() const;
float getAngle() const;

float getVelocityX() const;
float getVelocityY() const;



float getWidth() const;
float getHeight() const;

float getDensity() const;
float getFriction() const;
bool  getisDynamic() const;
float getLinearDamping() const;

void setX(float x);
void setY(float y);
void setAngle(float angle);

void setVelocityX(float velocityX);
void setVelocityY(float velocityY);


void draw() override; 


void update() override; 

void drawDebugShape() override;

//Setter for assigning the b2Body
void setBody(b2Body* body);

//getter for the b2Body
b2Body* getBody() const;




private:
   float _x;
   float _y;
   float _angle;
   float _velocityX;
   float _velocityY;
   float _width;
   float _height;
   float _density;
   float _friction;
   bool _isDynamic;
   float _linearDamping;
   b2Body* _body=nullptr;
};

#endif