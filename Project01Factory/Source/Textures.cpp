#include "Textures.h"

bool Textures::load(const std::string& key, const std::string& filepath, SDL_Renderer* renderer)
{
    SDL_Surface* tempSurface= IMG_Load(filepath.c_str()); 
    
    if (!tempSurface)
    {
        SDL_Log("Failed to load surface: %s", SDL_GetError());
        return false;
    }

//convert the surface into a texture
SDL_Texture* texture= SDL_CreateTextureFromSurface(renderer, tempSurface);
SDL_FreeSurface(tempSurface);


if (!texture) {
    SDL_Log("Failed to create texture: %s", SDL_GetError());
    return false;
}


// Store the texture in the map using a unique pointer
//using map std::unordered_map<std::string, 
// std::unique_ptr<SDL_Texture, SDL_Deleter>> textures;

textures[key]= std::unique_ptr<SDL_Texture, SDL_Deleter>(texture);
//key is given name of texture

return true;
}

SDL_Texture* Textures::get(const std::string& key)
{
   auto it= textures.find(key);
   if (it != textures.end())
   {
      return it->second.get();
     //return raw pointer to the texture 
   }
return nullptr;
}

void Textures::remove(const std::string& key)
{

textures.erase(key);
}

void Textures::clear()
{
textures.clear();
}



// Definition of static member
std::unordered_map<std::string, std::unique_ptr<SDL_Texture, Textures::SDL_Deleter>> Textures::textures;
