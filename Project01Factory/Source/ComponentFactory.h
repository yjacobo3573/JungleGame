#ifndef   COMPONENTFACTORY_H
#define   COMPONENTFACTORY_H
#include "Component.h"
#include "SpriteComponent.h"
#include"Component.h"
#include "GameObject.h"
#include "memory"
#include "tinyxml2.h"
#include<functional>
#include<unordered_map>
#include"ControllerComponent.h"
#include "SuperSpeedComponent.h"
#include "JumpComponent.h"

class ComponentFactory
{



public:
//create methods for each component
//create new objects

static std::unique_ptr<Component> createBodyComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement);


static std::unique_ptr<Component> createSpriteComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement);

static std::unique_ptr<Component> createControllerComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement);

static std::unique_ptr<Component> createSuperSpeedComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement);

static std::unique_ptr<Component> createJumpComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement);

//add components to the GameObject

 void registerComponent(const std::string& componentType, std::function<std::unique_ptr<Component>(GameObject&, const tinyxml2::XMLElement*)>creator);



//function to create Component
 std::unique_ptr<Component> createComponent(const std::string& componentType, GameObject& owner, const tinyxml2::XMLElement* element);



//register them to map


protected:

 std::unordered_map<std::string, std::function<std::unique_ptr<Component>(GameObject&, const tinyxml2::XMLElement*)>> ComponentLibrary;




};

#endif