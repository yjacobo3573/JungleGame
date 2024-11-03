#ifndef   TEXTURES_H
#define   TEXTURES_H
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <unordered_map>
#include <string>
#include <memory>

class Textures
{

public:

//load a texture from a file and store it with the given key
	static bool load(const std::string& key, const std::string& filepath, SDL_Renderer* renderer);

//get a texture by its key
	static SDL_Texture* get(const std::string& key);

//Remove a texture by its key
static void remove(const std::string& key);

//clear all textures
static void clear();


private:
//Custom deleter for SDL_Texture 
// to handle SDL_DestroyTexture automatically
	struct SDL_Deleter {
		void operator()(SDL_Texture* texture) const {
			if (texture)
			{
				SDL_DestroyTexture(texture);
			}
		}
};


//static map to store textures with custom keys 
// and unique_ptrs for automatic cleanup
static std::unordered_map<std::string, std::unique_ptr<SDL_Texture, SDL_Deleter>> textures;
	

    



};










#endif