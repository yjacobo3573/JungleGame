#include "GameObject.h"


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