#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "ShaderProgram.h"
#include "Texture2D.h"

namespace Renderer
{
	class Texture2D;
	class Texture2D;

	class Sprite
	{
	public:
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		Sprite(const std::shared_ptr<Texture2D>, const std::shared_ptr<ShaderProgram>, const glm::vec2&, const glm::vec2&, const float);
		~Sprite();

		void render() const;
		void setPosition(const glm::vec2&);
		void setSize(const glm::vec2&);
		void setRotation(const float);

	private:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
		GLuint m_VAO;
		GLuint m_vertexCoordsVBO;
		GLuint m_textureCoordsVBO;
	};
}