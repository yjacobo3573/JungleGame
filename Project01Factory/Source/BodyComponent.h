#ifndef   BODYCOMPONENT_H
#define   BODYCOMPONENT_H
#include <Box2D/Box2D.h>

#include "Component.h"

//Manages basic physics (position, angle, velocity).


class BodyComponent: public Component
{
public:

BodyComponent(GameObject& owner, double x, double y, double angle, double velocityX, double velocityY, int width, int height, float density, float friction, bool isDynamic, float linearDamping )
    : Component(owner),_x(x), _y(y), _angle(angle), _velocityX(velocityX), _velocityY(velocityY), _width(width), _height(height), _density(density), _friction(friction), _isDynamic(isDynamic), _linearDamping(linearDamping) {}


BodyComponent()=default;

double getX() const;
double getY() const;
double getAngle() const;

double getVelocityX() const;
double getVelocityY() const;



int getWidth() const;
int getHeight() const;

float getDensity() const;
float getFriction() const;
bool  getisDynamic() const;
float getLinearDamping() const;

void setX(double x);
void setY(double y);
void setAngle(double angle);

void setVelocityX(double velocityX);
void setVelocityY(double velocityY);


void draw() override; 


void update() override; 

//Setter for assigning the b2Body
void setBody(b2Body* body);

//getter for the b2Body
b2Body* getBody() const;




private:
   double _x;
   double _y;
   double _angle;
   double _velocityX;
   double _velocityY;
   int _width;
   int _height;
   float _density;
   float _friction;
   bool _isDynamic;
   float _linearDamping;
   b2Body* _body=nullptr;
};

#endif