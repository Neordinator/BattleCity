#pragma once

#include <glad/glad.h>
#include <vector>

namespace Renderer
{
	struct VertexBufferLayoutElement
	{
		GLint count;
		GLenum type;
		GLboolean normalized;
		unsigned int size;
		VertexBufferLayoutElement(GLint, GLenum, GLboolean, unsigned int);
	};
	class VertexBufferLayout
	{
	public:
		/*VertexBufferLayout(const VertexBufferLayout&) = delete;
		VertexBufferLayout& operator=(const VertexBufferLayout&) = delete;*/

		VertexBufferLayout();
		/*~VertexBufferLayout();
		VertexBufferLayout(VertexBufferLayout&&) noexcept;
		VertexBufferLayout& operator=(VertexBufferLayout&&) noexcept;*/

		void reserveElements(const size_t count);
		unsigned int getStride() const;
		void addElementLayoutFloat(const GLint count, const bool normalized);
		const std::vector<VertexBufferLayoutElement>& getLayoutElements() const;

	private:
		std::vector<VertexBufferLayoutElement> m_layoutElemets;
		unsigned int m_stride;
	};
}