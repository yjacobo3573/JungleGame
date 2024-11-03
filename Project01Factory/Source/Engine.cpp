#include "Engine.h" 
#include"ComponentFactory.h"
#include"GameObject.h"
#include "BodyComponent.h"

SDL_Renderer* Engine::renderer = nullptr;


Engine::Engine()
{
isRunning=false;
width=0;
window=nullptr;

compoLibrary= std::make_unique<ComponentFactory>();

compoLibrary->registerComponent("BodyComponent", [](GameObject& owner, const tinyxml2::XMLElement* element) {
    return ComponentFactory::createBodyComponent(owner, element);
    });

compoLibrary->registerComponent("SpriteComponent",
    [](GameObject& owner, const tinyxml2::XMLElement* element) {
        return ComponentFactory::createSpriteComponent(owner, element);
    });

compoLibrary->registerComponent("ControllerComponent",
    [](GameObject& owner, const tinyxml2::XMLElement* element) {
        return ComponentFactory::createControllerComponent(owner, element);
    });

compoLibrary->registerComponent("SuperSpeedComponent",
    [](GameObject& owner, const tinyxml2::XMLElement* element) {
        return ComponentFactory::createSuperSpeedComponent(owner, element);
    });

compoLibrary->registerComponent("JumpComponent",
    [](GameObject& owner, const tinyxml2::XMLElement* element) {
        return ComponentFactory::createJumpComponent(owner, element);
    });
}

int Engine::loadLevel()
{
    // Initialize the engine
    if (!init("SDL2 Game Engine", 800, 600)) {
        return -1;
    }

    
    // Load textures into the texture manager
    Textures::load("Player", "Assets/Run (7).png", renderer);
    Textures::load("Enemy", "Assets/JungleBackground.png", renderer);

    if (!Textures::load("Player", "Assets/Run (7).png", renderer)) {
        SDL_Log("Texture failed to load");
    }
    if (!Textures::load("Enemy", "Assets/treeLog.png", renderer)) {
        SDL_Log("Texture failed to load");
    }

    std::unique_ptr<GameObject>player = std::make_unique<GameObject>();
    std::unique_ptr<GameObject>enemy = std::make_unique<GameObject>();


//Load the XML document
tinyxml2::XMLDocument doc;
if (doc.LoadFile("Assets/Object.xml") == tinyxml2::XML_SUCCESS) {
    std::cout << "XML file loaded successfully!" << std::endl;
}
else {
    std::cerr << "Failed to load XML file." << std::endl;
}


// Get the root element
const tinyxml2::XMLElement* root = doc.RootElement();

//loop for player components
for (const tinyxml2::XMLElement* objectElem = root->FirstChildElement("Object"); objectElem != nullptr; objectElem = objectElem->NextSiblingElement("Object")) {
    if (std::string(objectElem->Attribute("type")) == "Player") {
        for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
            auto component = compoLibrary->createComponent(componentElem->Name(), *player, componentElem);
            if (component) {
                std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
                player->add(std::move(component));
               
            }
            else {
                std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
            }
        

    }
        }


}

// Loop for Enemy components
for (const tinyxml2::XMLElement* objectElem = root->FirstChildElement("Object"); objectElem != nullptr; objectElem = objectElem->NextSiblingElement("Object")) {
    if (std::string(objectElem->Attribute("type")) == "Enemy") {
        for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
            auto component = compoLibrary->createComponent(componentElem->Name(), *enemy, componentElem);
            if (component) {
                std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
               enemy->add(std::move(component));
            }
            else {
                std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
            }
        }
    }
}
//auto bodyComponent = std::make_unique<BodyComponent>(player, 2,3,4,5,6,7,8);
//player->add(std::move(bodyComponent));
//
//// Test retrieval
//auto retrievedBody = player->get<BodyComponent>();
//if (retrievedBody) {
//    std::cout << "BodyComponent successfully retrieved!" << std::endl;
//}
//else {
//    std::cerr << "Failed to retrieve BodyComponent." << std::endl;
//}


//Add game objects to the engine
addGameObject(std::move(player));
addGameObject(std::move(enemy));




run();

}

bool Engine::init(const char* title, int width, int height)
{
   this->width = width;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("Failed to initialize SDL_image for PNG support: %s", IMG_GetError());
        return false;
    }

    isRunning = true;
    return true;
}

void Engine::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        Input::processEvent(event);  // Call static Input method
    }
}

void Engine::update()
{
    for (auto& gameObject : gameObjects) {
        gameObject->update();  // Update each GameObject
    }
}

void Engine::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (auto& gameObject : gameObjects) {
        gameObject->draw();  // Draw each GameObject
    }

    SDL_RenderPresent(renderer);
}

void Engine::clean()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();

}

bool Engine::running()
{
    return isRunning;
}

void Engine::addGameObject(std::unique_ptr<GameObject> gameObject)
{

    gameObjects.push_back(std::move(gameObject));  // Add the game object to the list
}

void Engine::run()
{

    while (isRunning) {

       handleEvents();
       update();
       render();
       SDL_Delay(16);
    }
      clean();
}

SDL_Renderer* Engine::getRenderer()
{
    return renderer;
}
