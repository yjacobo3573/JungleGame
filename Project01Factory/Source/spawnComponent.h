#ifndef   SPAWNCOMPONENT_H
#define   SPAWNCOMPONENT_H
#include "Component.h"
#include "Input.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Engine.h"
#include  <memory.h>

class Engine;
class spawnComponent : public Component {

public:

   spawnComponent(GameObject& parent) : Component(parent), owner(parent) {}

   void update() override;

   void draw() override;

   void drawDebugShape() override;

   std::unique_ptr<Engine>engine= std::make_unique<Engine>();

   GameObject& owner;
  
};









#endif
