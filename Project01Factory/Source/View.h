#ifndef   VIEW_H
#define   VIEW_H
#include "SDL2/SDL.h"
class View
{

public:

//default constructor
View();

//parameterized constructor
View(float x, float y, float scale, float angle);

//sets the center position of the view
void setCenter(float x,float y);

//sets the zoom level of the view
void setScale(float scale);

//sets the rotation angle of the view (in degrees)
void setRotation(float angle);


//returns the current scale (zoom level) of the view
float getScale() const;

//returns the current rotation angle of the view
float getRotation() const;

//returns the center position of the view as an SDL_Point struct
SDL_Point getCenter() const;

//transforms a point from world coordinates to view(screen) coordinates
SDL_Point worldToView(const SDL_Point& worldPoint) const;

//transforms a rectangle from world coordinates to view(screen) coordinates
SDL_Rect worldToView(const SDL_Rect& worldRect) const;





private:
  float x; //center of the view in world coordinates
  float y;
  float scale; //zoom level
  float angle; //rotation angle in degrees

};

#endif