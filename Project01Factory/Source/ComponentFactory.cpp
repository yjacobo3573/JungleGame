#include "ComponentFactory.h"
#include "BodyComponent.h"
#include "Component.h"
#include "memory"
#include<string>
#include<iostream>



std::unique_ptr<Component> ComponentFactory::createBodyComponent(GameObject& owner,const tinyxml2::XMLElement* objectElement)
{


	if (std::string(objectElement->Name()) != "BodyComponent")
	{

    std::cerr<< "Error: Expected BodyComponent element";
    return nullptr;
   }



//retrieve each attribute and assign to variables
float x= objectElement->FloatAttribute("x", 0.0f);
float y= objectElement->FloatAttribute("y", 0.0f);
int width= objectElement->FloatAttribute("width", 0);
int height= objectElement->FloatAttribute("height", 0);
float velocityX= objectElement->FloatAttribute("velocityX", 0.0f);
float velocityY= objectElement->FloatAttribute("velocityY", 0.0f);
float angle= objectElement->FloatAttribute("angle", 0.0f);
float density=objectElement->FloatAttribute("density", 0.0f);
float friction=objectElement->FloatAttribute("friction", 0.0f);
bool isDynamic=objectElement->BoolAttribute("isDynamic", false);
float linearDamping= objectElement->FloatAttribute("linearDamping", 0.0f);


//create and return a new BodyComponent instance using parsed values

return std::make_unique<BodyComponent>(owner, x, y, angle, velocityX, velocityY, width, height, density, friction, isDynamic, linearDamping);



}

std::unique_ptr<Component> ComponentFactory::createSpriteComponent(GameObject& owner,const tinyxml2::XMLElement* objectElement)
{
	
	if (std::string(objectElement->Name()) != "SpriteComponent")
	{

		std::cerr << "Error: Expected SpriteComponent element";
		return nullptr;
	}

const char* textureKeyAttr = objectElement->Attribute("textureKey");

if (textureKeyAttr == nullptr) {
	std::cerr << "Error: Missing textureKey attribute in SpriteComponent element" << std::endl;
	return nullptr;
	}

std::string TextureKey= textureKeyAttr;


//create and return a new SpriteComponent instance
return std::make_unique<SpriteComponent>(owner, TextureKey);


}

std::unique_ptr<Component> ComponentFactory::createControllerComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement)
{
	return std::make_unique<ControllerComponent>(owner);
}

std::unique_ptr<Component> ComponentFactory::createSuperSpeedComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement)
{
	return std::make_unique<SuperSpeedComponent>(owner);
}

std::unique_ptr<Component> ComponentFactory::createJumpComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement)
{
	return std::make_unique<JumpComponent>(owner);
}

std::unique_ptr<Component> ComponentFactory::createCameraFollowerComponent(GameObject& owner, const tinyxml2::XMLElement* objectElement)
{
	return std::make_unique<CameraFollowerComponent>(owner);
}

void ComponentFactory::registerComponent(const std::string& componentType, std::function<std::unique_ptr<Component>(GameObject& ,const tinyxml2::XMLElement*)> creator)
{


ComponentLibrary[componentType] = creator;


}

std::unique_ptr<Component> ComponentFactory::createComponent(const std::string& componentType, GameObject& owner, const tinyxml2::XMLElement* element)
{
	auto it= ComponentLibrary.find(componentType);
	if (it != ComponentLibrary.end())
	{
		return it->second(owner, element); //call the stored create function
	}
    std::cerr<<"Error: Component type "<<componentType<< " not found in factory."<<std::endl;

return nullptr;
}


