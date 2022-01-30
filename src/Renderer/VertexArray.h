#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

namespace Render
{
	class VertexArray
	{
	public:
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray();
		~VertexArray();
		VertexArray(VertexArray&&) noexcept;
		VertexArray& operator=(VertexArray&&) noexcept;

		void addBuffer(const VertexBuffer&, const VertexBufferLayout&);
		void bind() const;
		void unbind() const;

	private:
		GLuint m_id = 0;
		unsigned int m_elementsCount = 0;
	};
}