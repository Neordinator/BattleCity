#include "VertexBufferLayout.h"

namespace Render
{
	VertexBufferLayoutElement::VertexBufferLayoutElement(GLint _count, GLenum _type, GLboolean _normalized, unsigned int _size)
	{
		count = _count;
		type = _type;
		normalized = _normalized;
		size = _size;
	}
	VertexBufferLayout::VertexBufferLayout() : m_stride(0)
	{
	}
	void VertexBufferLayout::reserveElements(const size_t count)
	{
		m_layoutElemets.reserve(count);
	}
	unsigned int VertexBufferLayout::getStride() const
	{
		return m_stride;
	}
	void VertexBufferLayout::addElementLayoutFloat(const GLint count, const bool normalized)
	{
		m_layoutElemets.push_back({ static_cast<GLint>(count), GL_FLOAT, normalized, count * static_cast<unsigned int>(sizeof(GLfloat)) });
		m_stride += m_layoutElemets.back().size;
	}
	const std::vector<VertexBufferLayoutElement>& VertexBufferLayout::getLayoutElements() const
	{
		return m_layoutElemets;
	}
}