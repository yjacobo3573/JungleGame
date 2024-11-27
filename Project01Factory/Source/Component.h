#ifndef   COMPONENT_H
#define   COMPONENT_H
#include  <typeindex>

class GameObject;

class Component
{
public:

//constructor to intialize passed in parent to the member
//GameObject& _parent
   explicit Component(GameObject& parent): _parent(parent) {}

    virtual void update()=0;
    virtual void draw()=0;
 

    virtual ~Component()=default;


//protected:
    GameObject& parent() const;
    
private:
GameObject& _parent;
//store a reference
};


#endif