#include "SpriteComponent.h"
#include "Engine.h"

void SpriteComponent::update()
{
}

void SpriteComponent::draw()
{
    auto body = parent().get<BodyComponent>();

    if (!body) {
        std::cerr << "BodyComponent not found!" << std::endl; // Enhanced error logging
        return; // Exit early if there's no body
    }

    SDL_Rect dst = { static_cast<int>(body->getX()), static_cast<int>(body->getY()),
                     static_cast<int>(body->getWidth()), static_cast<int>(body->getHeight()) };
    
    //transform the destination rectangle to view (screen) coordinates
    dst= Engine::view.worldToView(dst);
    
    int angle = static_cast<int>(body->getAngle());

    if (!Engine::getRenderer()) {
        SDL_Log("Renderer not initialized properly.");
        return; // Exit if the renderer is not valid
    }

    // Render with rotation
    SDL_RenderCopyEx(Engine::getRenderer(), texture, nullptr, &dst, angle, nullptr, SDL_FLIP_NONE);
}




