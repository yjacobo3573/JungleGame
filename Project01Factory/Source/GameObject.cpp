#include "GameObject.h"


GameObject::GameObject(const std::string& type) :type(type)
{
}

//update all components.
void GameObject::update() {
    for (auto& pair : components) {
        pair.second->update();
    }
}

//Draw all components.
void GameObject::draw() {

    for (auto& pair : components) {
        pair.second->draw();
    }

}

std::string GameObject::getType() const
{
    return type;
}
