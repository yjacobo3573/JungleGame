#include "Engine.h"
#include"ComponentFactory.h"
#include"GameObject.h"
#include <Box2D/Box2D.h>
#include"GameObject.h"
#include "BodyComponent.h"
#include"Component.h"
#include<chrono>  //for precise time measurement
#include<memory>
#include<iostream>

SDL_Renderer* Engine::renderer = nullptr;
float Engine::deltaTime = 0.0f;
View Engine::view(750.0f, 376.0f, 1.0f, 0.0f); // Initialize view with default center, scale, and rotation
const float Engine::SCALE = 100.0f;

Engine::Engine() :world(b2Vec2(0.0f, 9.8f))
 
{

	GameObject object; // Create a temporary GameObject
	bodyComponent = std::make_unique<BodyComponent>(
		object,       // Owner
		0.0, 0.0,     // x, y
		0.0,          // Angle
		0.0, 0.0,     // VelocityX, VelocityY
		100, 100,     // Width, Height
		1.0f,         // Density
		0.5f,         // Friction
		true,         // isDynamic
		0.0f          // LinearDamping
	);
	isRunning = false;
	width = 0;
	window = nullptr;
  
	compoLibrary = std::make_unique < ComponentFactory >();
   

	compoLibrary->registerComponent("BodyComponent", [](GameObject& owner,
		const tinyxml2::XMLElement* element) {
			return ComponentFactory::createBodyComponent(owner, element);
		});

	compoLibrary->registerComponent("SpriteComponent",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createSpriteComponent(owner, element);
		});

	compoLibrary->registerComponent("ControllerComponent",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createControllerComponent(owner, element);
		});

	compoLibrary->registerComponent("SuperSpeedComponent",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createSuperSpeedComponent(owner, element);
		});

	compoLibrary->registerComponent("JumpComponent",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createJumpComponent(owner, element);
		});

	compoLibrary->registerComponent("CameraFollowerComponent",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createCameraFollowerComponent(owner, element);
		});
}

int Engine::loadLevel() {
	// Initialize the engine
	if (!init("SDL2 Game Engine", SCREEN_WIDTH, SCREEN_HEIGHT)) {
		return -1;
	}

	// Load textures into the texture manager
	tinyxml2::XMLDocument doc;
	// Load the XML file directly from "Assets/Assets.xml"
	if (doc.LoadFile("Assets/Assets.xml") != tinyxml2::XML_SUCCESS) {
		std::cerr << "Failed to load XML file: Assets/Assets.xml" << std::endl;
		return -1;
	}

	// Access the root node (e.g., <Level1>)
	tinyxml2::XMLElement* level = doc.FirstChildElement("Level1");
	if (!level) {
		std::cerr << "No <Level1> element found in XML file." << std::endl;
		return -1;
	}

	// Loop through each <Asset> element

	for (tinyxml2::XMLElement* asset = level->FirstChildElement("Asset"); asset != nullptr; asset = asset->NextSiblingElement("Asset")) {
		const char* type = asset->Attribute("type"); // e.g., "Player", "Enemy", "Background"
		tinyxml2::XMLElement* textFileElement = asset->FirstChildElement("textFile");
		if (type && textFileElement) {
			const char* file = textFileElement->Attribute("file");
			if (file) {
				// Load the texture from the specified file
				std::string filePath = "Assets/" + std::string(file);
				if (!Textures::load(type, filePath, renderer)) {
					std::cerr << "Failed to load texture: " << type << " from " << filePath << std::endl;
				}
			}
			else {
				std::cerr << "No 'file' attribute found in <textFile> for asset type: " << type << std::endl;
			}
		}
		else {
			std::cerr << "Invalid <Asset> element or missing 'type' attribute." << std::endl;
		}
	}





	std::unique_ptr < GameObject > player = std::make_unique < GameObject >("Player");
	std::unique_ptr < GameObject > enemy = std::make_unique < GameObject >("Enemy");
	std::unique_ptr < GameObject > background = std::make_unique < GameObject >("Background");
	std::unique_ptr < GameObject > mushroomEnemy = std::make_unique < GameObject >("evilMushroom");

	//Load the XML document

	if (doc.LoadFile("Assets/Object.xml") == tinyxml2::XML_SUCCESS) {
		std::cout << "XML file loaded successfully!" << std::endl;
	}
	else {
		std::cerr << "Failed to load XML file." << std::endl;
	}

	// Get the root element
	tinyxml2::XMLElement* root = doc.RootElement();

	//loop for background component
	for (const tinyxml2::XMLElement* objectElem = root->FirstChildElement("Object"); objectElem != nullptr; objectElem = objectElem->NextSiblingElement("Object"))
	{
		if (std::string(objectElem->Attribute("type")) == "Background") {
			for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement())
			{
				auto component = compoLibrary->createComponent(componentElem->Name(), *background, componentElem);
				if (component) {
					std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
					background->add(std::move(component));

				}
				else {
					std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
				}
			}
		}
	}




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

	// Loop for Log Enemy components
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

    //Loop for Mushroom enemy components
	for (const tinyxml2::XMLElement* objectElem = root->FirstChildElement("Object"); objectElem != nullptr; objectElem = objectElem->NextSiblingElement("Object")) {
		if (std::string(objectElem->Attribute("type")) == "evilMushroom") {
			for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
				auto component = compoLibrary->createComponent(componentElem->Name(), *mushroomEnemy, componentElem);
				if (component) {
					std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
					mushroomEnemy->add(std::move(component));
				}
				else {
					std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
				}
			}
		}
	}
	//Add game objects to the engine
	addGameObject(std::move(player));
	addGameObject(std::move(enemy));
	addGameObject(std::move(background));
    addGameObject(std::move(mushroomEnemy));


	// create physics world bodies
	physicsWorld();

	run();

}

bool Engine::init(const char* title, int width, int height) {
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

void Engine::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		Input::processEvent(event); // Call static Input method

		
	}
}

void Engine::update() {


     
	world.Step(deltaTime, 6, 2);
   checkCollisions();
	
	
	for (auto& gameObject : gameObjects) {
		gameObject->update(); // Update each GameObject
	  
     }

	
	
}

void Engine::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	for (auto& gameObject : gameObjects) {
		if (gameObject->getType() == "Background") {
			gameObject->draw(); // Draw background 1st
		}
	}
	for (auto& gameObject : gameObjects) {
		if (gameObject->getType() != "Background") {
			gameObject->draw(); // Draw remaining items
		}
	}

	SDL_RenderPresent(renderer);
}

void Engine::clean() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();

}

bool Engine::running() {
	return isRunning;
}

void Engine::addGameObject(std::unique_ptr < GameObject > gameObject) {

	gameObjects.push_back(std::move(gameObject)); // Add the game object to the list
}

void Engine::run() {
	using clock = std::chrono::high_resolution_clock;

	while (isRunning) {

		//record start time
		auto frameStartTime = clock::now(); //capture the start time for the current frame to measure how long it takes.


		handleEvents();
		update();
		render();

		//calculate frame duration
		auto frameEndTime = clock::now(); //capture the end time after rendering the frame.

		std::chrono::duration<float, std::milli> elapsed = frameEndTime - frameStartTime;
		//calculate the elasped time between frame start and end in milliseconds.

		deltaTime = elapsed.count() / 1000.0f; //convert the elapsed time(in milliseconds) to seconds and store it in deltaTime
		//for use in game logic

		//frame rate limiting
		float frameElaspedMs = elapsed.count(); //get frame time in milliseconds.
		if (frameElaspedMs < frameDuration) { //frame duration= 16.67 ms

			SDL_Delay(static_cast<Uint32>(frameDuration - frameElaspedMs)); //delay the frame for the remaining time to maintain a consistent frame rate

		}
		//update deltaTime for the next loop iteration
		frameEndTime = clock::now(); //record the end time again after the potential delay.
		elapsed = frameEndTime - frameStartTime; //recalculate the elapsed time to get the final duration of this frame.
		deltaTime = elapsed.count() / 1000.0f; //store the final deltaTime after the delay, ensuring that it reflects the actual time taken for this frame

	}
	clean();
}

SDL_Renderer* Engine::getRenderer() {
	return renderer;
}

b2Body* Engine::CreateBox(b2World& world, float x, float y, float width, float height, bool isDynamic, float density, float friction, float linearDamping)
{
	b2BodyDef bodyDef; // A structure that holds information about 
	// the body, like its type and position.

	bodyDef.position.Set(x / SCALE, y / SCALE); //converts pixels to meters

	if (isDynamic) {
		bodyDef.type = b2_dynamicBody;
	}

	else {
		bodyDef.type = b2_staticBody;
	}

	b2Body* body = world.CreateBody(&bodyDef);

	//Define the shape
	b2PolygonShape boxShape;
	boxShape.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);

	//Define the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;


	body->CreateFixture(&fixtureDef);

	// bodyComponent->setBody(body); //set Box2D body in BodyComponent


	return body;
}

void Engine::physicsWorld()
{

	//create box2d world
	std::string groundTag = "Ground";
	b2Body* ground = CreateBox(world, 0, 470, 3500, 10, false, 1.0f, 0.3f, 2);
	//ground->GetUserData().pointer = reinterpret_cast<uintptr_t>(&groundTag);

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->getType() == "Player") {
			auto body = gameObject->get<BodyComponent>();
			if (body) {
				std::string playerTag = "Player";

				b2Body* dynamicPlayer = CreateBox(world, body->getX(), body->getY(), body->getWidth(), body->getHeight(), body->getisDynamic(), body->getDensity(), body->getFriction(), 2);

				body->setBody(dynamicPlayer);

				dynamicPlayer->GetUserData().pointer = reinterpret_cast<uintptr_t>(gameObject.get()); //address to game object
				//std::cout<<body->getY()<<std::endl;

			}
			else {
				std::cout << "Null body." << std::endl;
			}
			continue;

		}

		if (gameObject->getType() == "evilMushroom") {
			auto body = gameObject->get<BodyComponent>();

			if (body) {
				std::string mushroomTag = "evilMushroom";

				b2Body* evilMushroom = CreateBox(world, body->getX(), body->getY(), body->getWidth(), body->getHeight(), body->getisDynamic(), body->getDensity(), body->getFriction(), 2);

				body->setBody(evilMushroom);
				evilMushroom->GetUserData().pointer = reinterpret_cast<uintptr_t>(gameObject.get());

				//std::cout <<body->getWidth()<<std::endl;
			}

			else {
				std::cout << "Null body." << std::endl;
			}
			continue;
		}
	}




}

void Engine::checkCollisions()
{
	//collision detection
	for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
		if (contact->IsTouching()) {
			auto* objA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
			auto* objB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

			if (objA && objB) {  //ensure objects are not null
				if ((objA->getType() == "evilMushroom" && objB->getType() == "Player") ||
					(objA->getType() == "Player" && objB->getType() == "evilMushroom")){

                    std::cout<<"Collision detected between Player and evilMushroom!"<<std::endl;
				 }
		   }
			
		}
	}

}

