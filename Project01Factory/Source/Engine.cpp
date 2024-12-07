#include "Engine.h"




#include<chrono>  //for precise time measurement
#include<memory>
#include<iostream>

SDL_Renderer* Engine::renderer = nullptr;
float Engine::deltaTime = 0.0f;
View Engine::view(750.0f, 376.0f, 1.0f, 0.0f); // Initialize view with default center, scale, and rotation
const float Engine::SCALE = 100.0f;

const int Engine::SCREEN_HEIGHT=752;
const int Engine::SCREEN_WIDTH=1500;
Mix_Chunk* Engine::thumpSoundEffect = nullptr; 
Mix_Chunk* Engine::footStepsSound = nullptr; 
std::vector<std::unique_ptr<GameObject>> Engine::toAdd;
std::vector<std::unique_ptr<GameObject>> Engine::gameObjects;

Engine::Engine() :world(b2Vec2(0.0f, 9.8f))
 
{

	destroyAllBodies();
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

	compoLibrary->registerComponent("DamageComponent",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createDamageComponent(owner, element);
		});

	compoLibrary->registerComponent("spawnComponent",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createspawnComponent(owner, element);
		});

	compoLibrary->registerComponent("AIComponentPatroling",
		[](GameObject& owner,
			const tinyxml2::XMLElement* element) {
				return ComponentFactory::createAIComponentPatroling(owner, element);
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
	std::unique_ptr < GameObject > log = std::make_unique < GameObject >("treeLog");

	std::unique_ptr < GameObject > background = std::make_unique < GameObject >("Background");
	std::unique_ptr < GameObject > mushroomEnemy = std::make_unique < GameObject >("evilMushroom");
	std::unique_ptr < GameObject > bee = std::make_unique < GameObject >("bee");
   

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

	// Loop for Log components
	for (const tinyxml2::XMLElement* objectElem = root->FirstChildElement("Object"); objectElem != nullptr; objectElem = objectElem->NextSiblingElement("Object")) {
		if (std::string(objectElem->Attribute("type")) == "treeLog") {
			for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
				auto component = compoLibrary->createComponent(componentElem->Name(), *log, componentElem);
				if (component) {
					std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
				    log->add(std::move(component));
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


//Loop for Bee components
	for (const tinyxml2::XMLElement* objectElem = root->FirstChildElement("Object"); objectElem != nullptr; objectElem = objectElem->NextSiblingElement("Object")) {
		if (std::string(objectElem->Attribute("type")) == "bee") {
			for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
				auto component = compoLibrary->createComponent(componentElem->Name(), *bee, componentElem);
				if (component) {
					std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
					bee->add(std::move(component));
				}
				else {
					std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
				}
			}
		}
	}




	//Add game objects to the engine
	addGameObject(std::move(player));
	addGameObject(std::move(log));
	addGameObject(std::move(background));
    addGameObject(std::move(mushroomEnemy)); 
    addGameObject(std::move(bee)); 


	// create physics world bodies
	physicsWorld();

	run();

}

int Engine::loadLevel2()
{
	
	
	// Load textures into the texture manager
	tinyxml2::XMLDocument doc;
	// Load the XML file directly from "Assets/Assets.xml"
	if (doc.LoadFile("Assets/AssetsLevel2.xml") != tinyxml2::XML_SUCCESS) {
		std::cerr << "Failed to load XML file: Assets/AssetsLevel2.xml" << std::endl;
		return -1;
	}

	// Access the root node (e.g., <Level2>)
	tinyxml2::XMLElement* level = doc.FirstChildElement("Level2");
	
    if (!level) {
		std::cerr << "No <Level2> element found in XML file." << std::endl;
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
	//Load the XML document

	if (doc.LoadFile("Assets/ObjectLevel2.xml") == tinyxml2::XML_SUCCESS) {
		std::cout << "XML file loaded successfully!" << std::endl;
	}
	else {
		std::cerr << "Failed to load XML file." << std::endl;
	}
	std::unique_ptr < GameObject > playerLevel2 = std::make_unique < GameObject >("PlayerLevel2");
	std::unique_ptr < GameObject > backgroundLevel2 = std::make_unique < GameObject >("BackgroundLevel2");
	std::unique_ptr < GameObject > evilPlantLevel2 = std::make_unique < GameObject >("EvilPlantLevel2");

	// Get the root element
	tinyxml2::XMLElement* root = doc.RootElement();

	//loop for player components
	for (const tinyxml2::XMLElement* objectElem = root->FirstChildElement("Object"); objectElem != nullptr; objectElem = objectElem->NextSiblingElement("Object")) {
		if (std::string(objectElem->Attribute("type")) == "PlayerLevel2") {
			for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
				auto component = compoLibrary->createComponent(componentElem->Name(), *playerLevel2, componentElem);
				if (component) {
					std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
					playerLevel2->add(std::move(component));

				}
				else {
					std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
				}

			}
		}
         //loop for background components
		if (std::string(objectElem->Attribute("type")) == "BackgroundLevel2") {
			for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
				auto component = compoLibrary->createComponent(componentElem->Name(), *backgroundLevel2, componentElem);
				if (component) {
					std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
					backgroundLevel2->add(std::move(component));

				}
				else {
					std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
				}

			}
		}

         //loop for evil plant components

		if (std::string(objectElem->Attribute("type")) == "EvilPlantLevel2") {
			for (const tinyxml2::XMLElement* componentElem = objectElem->FirstChildElement(); componentElem != nullptr; componentElem = componentElem->NextSiblingElement()) {
				auto component = compoLibrary->createComponent(componentElem->Name(), *evilPlantLevel2, componentElem);
				if (component) {
					std::cout << "Adding component from XML: " << componentElem->Name() << std::endl;
					evilPlantLevel2->add(std::move(component));

				}
				else {
					std::cerr << "Failed to create component: " << componentElem->Name() << std::endl;
				}

			}
		}

        

	}

   

	//Add game objects to the engine
    addGameObject(std::move(backgroundLevel2));
	addGameObject(std::move(playerLevel2));
	addGameObject(std::move(evilPlantLevel2));
	
    physicsWorldLevel2();
    run();

	
}



void Engine::deleteGameObjects()
{

	gameObjects.clear();
    
}

void Engine::destroyAllBodies()
{
	// Destroy all bodies in gameObjects
	for (auto& gameObj : gameObjects) {
		if (gameObj) {
			auto body = gameObj->get<BodyComponent>();
			if (body) {
				auto b2Body = body->getBody();
				if (b2Body) {
					b2Body->GetWorld()->DestroyBody(b2Body);
				}
			}
		}
	}
	deleteGameObjects(); // Clear the gameObjects vector after destruction
}



bool Engine::init(const char* title, int width, int height) {
	this->width = width;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048) < 0) {
		std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
		exit(1);
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

   thumpSoundEffect = Mix_LoadWAV("Assets/ThumpSound.wav");
	
	if (!thumpSoundEffect) {
		std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
	}

	footStepsSound = Mix_LoadWAV("Assets/walkingSound.wav");

	if (!footStepsSound) {
		std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
	}

	
	isRunning = true;
	return true;
}



void Engine::thumpSound() {
	Mix_VolumeChunk(thumpSoundEffect,MIX_MAX_VOLUME/2);
	int channel = Mix_PlayChannel(2, thumpSoundEffect, 0); // Use channel 2 for collisions
	if (channel == -1) {
		std::cerr << "Failed to play collision sound: " << Mix_GetError() << std::endl;
	}
}

void Engine::stepsSound()
{
	Mix_VolumeChunk(footStepsSound, MIX_MAX_VOLUME / 5);
	int channel = Mix_PlayChannel(1, footStepsSound, 0); // Use channel 1 for footsteps
	if (channel == -1) {
		std::cerr << "Failed to play footsteps sound: " << Mix_GetError() << std::endl;
	}

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


     //step the world
	world.Step(deltaTime, 6, 2);
   checkCollisions();  //check for collisions
	
	
	for (auto& gameObject : gameObjects) {
		gameObject->update(); // Update each GameObject
	  
     }

    // Add new objects after the loop
	for (auto& obj : toAdd) {
		gameObjects.push_back(std::move(obj));
	}
	toAdd.clear(); // Clear the temporary vector

	for (auto& gameObject : gameObjects) {
		if (gameObject->getType() == "Player") {
			auto body = gameObject->get<BodyComponent>();
			int x = body->getX();
std::cout<<x<<std::endl;
			if (body) {

				
				if (x >= 1300.0f) {
                //start clean and load level 2
					destroyAllBodies();
                
					loadLevel2();

				}
			}
		}
	}
	
}

void Engine::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	for (auto& gameObject : gameObjects) {
		if (gameObject->getType() == "Background" ) {
			gameObject->draw(); // Draw background 1st
		}
	}
	for (auto& gameObject : gameObjects) {
		if (gameObject->getType() != "Background" ) {
			gameObject->draw(); // Draw remaining items
            gameObject->drawDebugShape(); 
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
	if (gameObject) {

	
	gameObjects.push_back(std::move(gameObject)); // Add the game object to the list
		
    }
	else {
		std::cerr<<"Attempted to add null game object!";
	}
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


	//float adjustedWidth = width * 0.6f;
	//// Debug output
	//std::cout << "Original Width: " << width << ", Adjusted Width: " << adjustedWidth << std::endl;

	//Define the shape
	b2PolygonShape boxShape;
	boxShape.SetAsBox((width / 2.0f)/SCALE, (height/2.0f)/SCALE);

	//Define the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;


	body->CreateFixture(&fixtureDef);

	// bodyComponent->setBody(body); //set Box2D body in BodyComponent


	return body;
}

b2Body* Engine::CreatePlayerBody(b2World& world, float x, float y, float width, float height, bool isDynamic, float density, float friction, float linearDamping, bool includeHead) {
	// Null check for the world
	if (&world == nullptr) {
		std::cerr << "Error: Invalid b2World reference passed to CreateBody." << std::endl;
		return nullptr;
	}

	// Define the body
	b2BodyDef bodyDef;
	bodyDef.position.Set(x / SCALE, y / SCALE); // Keep y-axis as is
	bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
	bodyDef.linearDamping = linearDamping;

	// Create the body
	b2Body* body = world.CreateBody(&bodyDef);
	if (!body) {
		std::cerr << "Error: Failed to create b2Body." << std::endl;
		return nullptr;
	}

	// Define the torso (rectangle)
	b2PolygonShape torsoShape;
	torsoShape.SetAsBox((width / 2.0f) / SCALE, (height / 2.5f) / SCALE,
		b2Vec2(0, -height / 4.0f / SCALE), 0.0f); // Adjust offset for torso

	b2FixtureDef torsoFixtureDef;
	torsoFixtureDef.shape = &torsoShape;
	torsoFixtureDef.density = density;
	torsoFixtureDef.friction = friction;

	b2Fixture* torsoFixture = body->CreateFixture(&torsoFixtureDef);
	if (!torsoFixture) {
		std::cerr << "Error: Failed to create torso fixture." << std::endl;
		return nullptr; // Cleanup may be necessary
	}

	// Optionally include the head (circle)
	if (includeHead) {
		b2CircleShape headShape;
		headShape.m_radius = (width / 4.0f) / SCALE; // Adjust based on head size
		headShape.m_p.Set(0, height / 2.5f / SCALE); // Position above the torso

		b2FixtureDef headFixtureDef;
		headFixtureDef.shape = &headShape;
		headFixtureDef.density = density;
		headFixtureDef.friction = friction;

		b2Fixture* headFixture = body->CreateFixture(&headFixtureDef);
		if (!headFixture) {
			std::cerr << "Error: Failed to create head fixture." << std::endl;
			return nullptr; // Cleanup may be necessary
		}
	}

	return body;
}

void Engine::physicsWorld()
{

	//create box2d world
	std::string groundTag = "Ground";
	b2Body* ground = CreateBox(world, 0.0f, 480.0f, 3500.0f, 10.0f, false, 0.0f, 0.3f, 2.0f);
	//ground->GetUserData().pointer = reinterpret_cast<uintptr_t>(&groundTag);

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->getType() == "Player") {
			auto body = gameObject->get<BodyComponent>();
			if (body) {
				

				b2Body* dynamicPlayer = CreateBox(world, body->getX(), body->getY(), body->getWidth(), body->getHeight(), body->getisDynamic(), body->getDensity(), body->getFriction(), 2);
				if (!dynamicPlayer) {
					std::cerr << "Failed to create player body!" << std::endl;
				}
              body->setBody(dynamicPlayer);
               dynamicPlayer->SetBullet(true);

				dynamicPlayer->GetUserData().pointer = reinterpret_cast<uintptr_t>(gameObject.get()); //address to game object
				


			}
			else {
				std::cout << "Null body." << std::endl;
			}
			continue;

		}

		if (gameObject->getType() == "evilMushroom") {
			auto body = gameObject->get<BodyComponent>();

			if (body) {
				

				b2Body* evilMushroom = CreateBox(world, body->getX(), body->getY(), body->getWidth(), body->getHeight(), body->getisDynamic(), body->getDensity(), body->getFriction(), 2);
               std::cout<<body->getY()<<std::endl;
				body->setBody(evilMushroom);
				evilMushroom->SetType(b2_kinematicBody);

				evilMushroom->GetUserData().pointer = reinterpret_cast<uintptr_t>(gameObject.get());

				

				// Debugging output
				std::cout << "Mushroom created at: (" << evilMushroom->GetPosition().x << ", " << evilMushroom->GetPosition().y << ")" << std::endl;
				


			}

			else {
				std::cout << "Null body." << std::endl;
			}
			continue;
		}
	


	   if (gameObject->getType() == "treeLog") {
		auto body = gameObject->get<BodyComponent>();

		  if (body) {
			

			b2Body* treeLog = CreateBox(world, body->getX(), body->getY(), body->getWidth(), body->getHeight(), body->getisDynamic(), body->getDensity(), body->getFriction(), 2);

			body->setBody(treeLog);
            //treeLog->GetUserData().pointer = reinterpret_cast<uintptr_t>(gameObject.get());
			
			
		  }

		  else {
			std::cout << "Null body." << std::endl;
		  }
		continue;
	   }
    }

}

void Engine::physicsWorldLevel2()
{

	//create box2d world
	//std::string groundTag = "GroundLevel2";
	//b2Body* ground = CreateBox(world, 0.0f, 480.0f, 3500.0f, 10.0f, false, 0.0f, 0.3f, 2.0f);
	//ground->GetUserData().pointer = reinterpret_cast<uintptr_t>(&groundTag);

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->getType() == "PlayerLevel2") {
			auto body = gameObject->get<BodyComponent>();
			if (body) {


				b2Body* dynamicPlayerLevel2 = CreateBox(world, body->getX(), body->getY(), body->getWidth(), body->getHeight(), body->getisDynamic(), body->getDensity(), body->getFriction(), 2);

				body->setBody(dynamicPlayerLevel2);
				dynamicPlayerLevel2->SetBullet(true);

				dynamicPlayerLevel2->GetUserData().pointer = reinterpret_cast<uintptr_t>(gameObject.get()); //address to game object
				


			}
			else {
				std::cout << "Null body." << std::endl;
			}
			continue;

        }
		if (gameObject->getType() == "EvilPlantLevel2") {
			auto body = gameObject->get<BodyComponent>();
			if (body) {


				b2Body* staticPlantLevel2 = CreateBox(world, body->getX(), body->getY(), body->getWidth(), body->getHeight(), body->getisDynamic(), body->getDensity(), body->getFriction(), 2);

				body->setBody(staticPlantLevel2);
				
				staticPlantLevel2->GetUserData().pointer = reinterpret_cast<uintptr_t>(gameObject.get()); //address to game object



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

bool gameOver=false;
	//collision detection
	for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
		if (contact->IsTouching()) {
			auto* objA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
			auto* objB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

			if (objA && objB) {  //ensure objects are not null
				if ((objA->getType() == "Player" && (objB->getType() == "evilMushroom" )) ||
					(objB->getType() == "Player" && (objA->getType() == "evilMushroom" ))) {

                  

                  
                   //determine which object is the player and call its collision counter method
                   //call function handle collision to create a customized reaction to each enemy
				   if (objA->getType() == "Player") {
					   handleCollisions(objA, objB);
					   auto Damage= objA->get<DamageComponent>();
					   if (Damage) {
						   Damage->collisionCounter();
					  }
					   if (Damage && Damage->getIsAlive()==false ) {
						 
						   //endGame(objA); //Call to end the game
						   gameOver = true;
						   break;  //exit the loop early
                           
					   }
				   }
				   if (objB->getType() == "Player") {
					   handleCollisions(objB, objA);
					   auto Damage = objB->get<DamageComponent>();
					   if (Damage) {
						   Damage->collisionCounter();
					   }
					   if (Damage && Damage->getIsAlive()==false) {
						
						   //endGame(objB); //Call to end the game
                           gameOver= true;
                           break;  //exit the loop early
					   }
				   }

                }
                if ((objA->getType() == "PlayerLevel2" && objB->getType() == "EvilPlantLevel2") ||
					(objB->getType() == "PlayerLevel2" && objA->getType() == "EvilPlantLevel2")){
					//determine which object is the player and call its collision counter method
				  //call function handle collision to create a customized reaction to each enemy
					
                  if (objA->getType() == "PlayerLevel2") {
					  handleCollisions(objA, objB);
						auto Damage = objA->get<DamageComponent>();
						if (Damage) {
							Damage->collisionCounter();
						}
						if (Damage && Damage->getIsAlive() == false) {

							//endGame(objA); //Call to end the game
							gameOver = true;
							break;  //exit the loop early

						}
					}
					if (objB->getType() == "PlayerLevel2") {
						handleCollisions(objB, objA);
						auto Damage = objB->get<DamageComponent>();
						if (Damage) {
							Damage->collisionCounter();
						}
						if (Damage && Damage->getIsAlive() == false) {

							//endGame(objB); //Call to end the game
							gameOver = true;
							break;  //exit the loop early
						}
					}

		        }
			
		}
	}
}
	if (gameOver)
	{

        destroyAllBodies();
		isRunning = false; // Handle termination outside the loop
	}



}

void Engine::handleCollisions(GameObject* player, GameObject* enemy)
{

	if (enemy) { //if not null
		if (enemy->getType() == "evilMushroom") {
			thumpSound();
		}
		if (enemy->getType() == "EvilPlantLevel2") {
			thumpSound();
		}



   }
}

//void Engine::endGame(GameObject* gameObject)
//{
//
//  if(gameObject)
//  { 
//	auto body = gameObject->get<BodyComponent>();
//
//	if (body)
//	{
//      auto b2Body= body->getBody();
//      if(b2Body){
//		b2Body->GetWorld()->DestroyBody(body->getBody());
//      }
//	}
//	
//
//	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
//		if ((*it)->getType() == "Player" ) {
//			it = gameObjects.erase(it); // Safe erase with iterator
//			break; // Stop after erasing the first match
//		}
//	}
//
//    
//
//  }


//}

