#ifndef   GAMEOBJECT_H
#define   GAMEOBJECT_H
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>
#include <iostream>
#include "Component.h"  

template<typename T>

int getID() {
	return std::hash<std::type_index>()(std::type_index(typeid(T)));
}


class GameObject
{

public:
    template<typename T>
    void add(std::unique_ptr<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        components[std::type_index(typeid(*component))] = std::move(component);
        std::cout << "Added component of type: " << typeid(T).name() << std::endl;
    }



    // Get a component by type as a raw pointer
    template<typename T>
    T* get() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        std::cerr << "Component not found: " << typeid(T).name() << std::endl;
        return nullptr;
    }

//update all components.

void update();


void draw();


private:

  std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

}; 

#endif