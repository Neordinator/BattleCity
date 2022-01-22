#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "../Renderer/ShaderProgram.h"

namespace Renderer
{
	class ShaderProgram;
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
	void loadTexture(const std::string&, const std::string&);
private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	std::string m_path;

	std::string getFileString(const std::string&) const;
};