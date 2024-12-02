
#ifndef   DAMAGECOMPONENT_H
#define   DAMAGECOMPONENT_H

#include "Component.h"
#include "GameObject.h"

class DamageComponent : public Component {



public:

    DamageComponent(GameObject& owner, int collisions,bool isAlive) : Component(owner), collisions(collisions), isAlive(isAlive) {}

     
	void draw() override;


	void update() override;

    void drawDebugShape() override;


    void collisionCounter();

    void kill();

    bool getIsAlive();

private:

int collisions;
bool isAlive;
    

};





#endif