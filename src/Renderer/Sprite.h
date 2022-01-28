#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "ShaderProgram.h"
#include "Texture2D.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Renderer
{
	class Texture2D;
	class SubTexture2D;

	class Sprite
	{
	public:
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		Sprite(std::shared_ptr<Texture2D>, std::string, std::shared_ptr<ShaderProgram>, const glm::vec2&, const glm::vec2&, const float);
		~Sprite();

		virtual void render() const;
		void setPosition(const glm::vec2&);
		void setSize(const glm::vec2&);
		void setRotation(const float);

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;

		VertexArray m_vertexArray;
		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;
	};
}