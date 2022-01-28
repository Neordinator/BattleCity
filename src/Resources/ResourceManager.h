#pragma once

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

namespace Renderer
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

	static std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string&, const std::string&, const std::string&);
	static std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string&);

	static std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string&, const std::string&);
	static std::shared_ptr<Renderer::Texture2D> getTexture(const std::string&);

	static std::shared_ptr<Renderer::Sprite> loadSprite(const std::string&, const std::string&, const std::string&, const unsigned int, const unsigned int, const std::string& subTextureName = "default" );
	static std::shared_ptr<Renderer::Sprite> getSprite(const std::string&);

	static std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string&, const std::string&, const std::string&, const unsigned int, const unsigned int, const std::string&);
	static std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string&);

	static std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(std::string, std::string, std::vector<std::string>, const unsigned int, const unsigned int);

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	static SpritesMap m_sprites;

	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpritesMap;
	static AnimatedSpritesMap m_animatedSprites;

	static std::string m_path;


	static std::string getFileString(const std::string&);
};