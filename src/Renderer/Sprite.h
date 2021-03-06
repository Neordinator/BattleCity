#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>

namespace Render
{
	class Texture2D;
	class SubTexture2D;
	class ShaderProgram;

	struct FrameDescription
	{
		FrameDescription(const glm::vec2 _leftBottomUV, glm::vec2 _rightTopUV, double _duration)
			: leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV), duration(_duration)
		{}

		glm::vec2 leftBottomUV;
		glm::vec2 rightTopUV;
		double duration;
	};

	class Sprite
	{
	public:
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		Sprite(std::shared_ptr<Texture2D>, std::string, std::shared_ptr<ShaderProgram>);
		~Sprite();

		void render(const glm::vec2&, const glm::vec2&, const float, const float layer = 0, const size_t frameId = 0) const;

		void insertFrames(std::vector<FrameDescription>);
		double getFrameDuration(const size_t frameId) const;
		size_t getFramesCount() const;

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;

		VertexArray m_vertexArray;
		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;

		std::vector<FrameDescription> m_framesDescriptions;
		mutable size_t m_lastFrameId;
	};
}