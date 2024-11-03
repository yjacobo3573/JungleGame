#ifndef   BODYCOMPONENT_H
#define   BODYCOMPONENT_H

#include "Component.h"

//Manages basic physics (position, angle, velocity).
class BodyComponent: public Component
{
public:


BodyComponent(GameObject& owner, double x, double y, double angle, double velocityX, double velocityY, int width, int height)
    : Component(owner),_x(x), _y(y), _angle(angle), _velocityX(velocityX), _velocityY(velocityY), _width(width), _height(height) {}


double& getX();
double& getY();
double& getAngle();

double& getVelocityX();
double& getVelocityY();

int& getWidth();
int& getHeight();

void draw() override; 


void update() override; 

private:
   double _x;
   double _y;
   double _angle;
   double _velocityX;
   double _velocityY;
   int _width;
   int _height;


};

#endif