#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

#include <string>

namespace Render
{
	class Renderer
	{
	public:
		static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);
		static void setClearColor(float r, float g, float b, float a);
		static void setDepthTest(const bool);
		static void clear();
		static void setViewport(unsigned int width, unsigned int height, unsigned int leftOffset, unsigned int bottomOffset);

		static std::string getRendererStr();
		static std::string getVersionStr();
	};
}