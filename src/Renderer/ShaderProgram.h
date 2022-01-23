#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram(const std::string&, const std::string&);
		~ShaderProgram();
		ShaderProgram& operator=(ShaderProgram&&) noexcept;
		ShaderProgram(ShaderProgram&&) noexcept;
		void setInt(const std::string&, const GLint);
		bool isCompiled() const { return m_isCompiled; }
		void use() const;
	private:
		bool m_isCompiled{ false };
		GLuint m_ID{ 0 };

		bool createShader(const std::string&, const GLenum, GLuint&);
	};
}