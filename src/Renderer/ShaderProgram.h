#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace Render
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
		void setFloat(const std::string&, const GLfloat);
		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setMatrix4(const std::string&, const glm::mat4&);
	private:
		bool m_isCompiled{ false };
		GLuint m_ID{ 0 };

		bool createShader(const std::string&, const GLenum, GLuint&);
	};
}