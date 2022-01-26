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

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
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

	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string&, const std::string&, const std::string&, const unsigned int, const unsigned int, const std::string&);
	std::shared_ptr<Renderer::Sprite> getSprite(const std::string&);

	std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(const std::string&, const std::string&, const std::vector<std::string>, const unsigned int, const unsigned int);

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	SpritesMap m_sprites;

	std::string m_path;


	std::string getFileString(const std::string&) const;
};