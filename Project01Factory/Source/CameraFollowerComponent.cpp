#include "CameraFollowerComponent.h"
#include"iostream"
#include"BodyComponent.h"
#include "GameObject.h"
#include"Engine.h"
#include<algorithm>


void CameraFollowerComponent::draw()
{
}

void CameraFollowerComponent::update()
{

    auto body = parent().get<BodyComponent>();

    if (!body) {
        std::cerr << "BodyComponent not found!" << std::endl; // Enhanced error logging
        return; // Exit early if there's no body
    }
   
    // Get player position and set camera view to follow
    float playerX = static_cast<float>(body->getX());
    float playerY = static_cast<float>(body->getY());
    float backgroundWidth = 1500; 
    float backgroundHeight = 752; 

    // Defines camera boundaries to avoid showing white space
    float halfScreenWidth = 750.0f/1.4f; // Half of the screen width
    float halfScreenHeight = 376.0f/1.4f; // Half of the screen height

    // Clamp camera's x position
    float cameraX = std::clamp(playerX, halfScreenWidth, backgroundWidth - halfScreenWidth);

    // Clamp camera's y position
    float cameraY = std::clamp(playerY, halfScreenHeight, backgroundHeight - halfScreenHeight);
     
    Engine::view.setScale(1.4f);
    // Update the view with the clamped position and scale
    Engine::view.setCenter(cameraX, cameraY);
    
    Engine::view.setRotation(static_cast<float>(body->getAngle()));
}
