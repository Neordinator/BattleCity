#pragma once

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

namespace Render
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
}

class ResourceManager
{
public:
	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static void setExecutablePath(const std::string&);
	static void unloadAllResources();

	static std::shared_ptr<Render::ShaderProgram> loadShaders(const std::string&, const std::string&, const std::string&);
	static std::shared_ptr<Render::ShaderProgram> getShaderProgram(const std::string&);

	static std::shared_ptr<Render::Texture2D> loadTexture(const std::string&, const std::string&);
	static std::shared_ptr<Render::Texture2D> getTexture(const std::string&);

	static std::shared_ptr<Render::Sprite> loadSprite(const std::string&, const std::string&, const std::string&, const unsigned int, const unsigned int, const std::string&);
	static std::shared_ptr<Render::Sprite> getSprite(const std::string&);

	static std::shared_ptr<Render::AnimatedSprite> loadAnimatedSprite(const std::string&, const std::string&, const std::string&, const unsigned int, const unsigned int, const std::string&);
	static std::shared_ptr<Render::AnimatedSprite> getAnimatedSprite(const std::string&);

	static std::shared_ptr<Render::Texture2D> loadTextureAtlas(std::string, std::string, std::vector<std::string>, const unsigned int, const unsigned int);

	static bool loadJSONResources(const std::string& JSONPath);

private:
	typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Render::Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Render::Sprite>> SpritesMap;
	static SpritesMap m_sprites;

	typedef std::map<const std::string, std::shared_ptr<Render::AnimatedSprite>> AnimatedSpritesMap;
	static AnimatedSpritesMap m_animatedSprites;

	static std::string m_path;


	static std::string getFileString(const std::string&);
};