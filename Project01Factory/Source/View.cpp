#include "View.h"

View::View()
{
x=0.0f;

y=0.0f;

scale=1.0f;

angle=0.0f;
}

View::View(float x, float y, float scale, float angle) : x(x), y(y), scale(scale), angle(angle)
{
}

void View::setCenter(float x, float y)
{
this->x=x;
this->y=y;
}

void View::setScale(float scale)
{

this->scale=scale;
}

void View::setRotation(float angle)
{
this->angle=angle;
}

float View::getScale() const
{
	return scale;
}

float View::getRotation() const
{
	return angle;
}

SDL_Point View::getCenter() const
{
	return { static_cast<int>(x), static_cast<int>(y)};
}

SDL_Point View::worldToView(const SDL_Point& worldPoint) const
{
	SDL_Point viewPoint; //Create an SDL_Point to store transformed coordinates
    viewPoint.x= static_cast<int>((worldPoint.x-x) * scale+750); //transform x coordinate
    viewPoint.y= static_cast<int>((worldPoint.y-y) * scale+376); //transform y coordinate
    return viewPoint;
}

SDL_Rect View::worldToView(const SDL_Rect& worldRect) const
{
	SDL_Rect viewRect; //create an SDL_Rect to store transformed rectangle coordinates and size
    viewRect.x= static_cast<int>((worldRect.x-x) *scale+750); //transform x position
    viewRect.y=static_cast<int>((worldRect.y-y) *scale+376);
    viewRect.w= static_cast<int>(worldRect.w*scale);
    viewRect.h=static_cast<int>(worldRect.h*scale);
    return viewRect;
}
