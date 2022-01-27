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
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	ResourceManager() = default;
	ResourceManager(const std::string&);

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string&, const std::string&, const std::string&);
	std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string&);

	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string&, const std::string&);
	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string&);

	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string&, const std::string&, const std::string&, const unsigned int, const unsigned int, const std::string& subTextureName = "default" );
	std::shared_ptr<Renderer::Sprite> getSprite(const std::string&);

	std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string&, const std::string&, const std::string&, const unsigned int, const unsigned int, const std::string&);
	std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string&);

	std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(std::string, std::string, std::vector<std::string>, const unsigned int, const unsigned int);

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	SpritesMap m_sprites;

	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpritesMap;
	AnimatedSpritesMap m_animatedSprites;

	std::string m_path;


	std::string getFileString(const std::string&) const;
};