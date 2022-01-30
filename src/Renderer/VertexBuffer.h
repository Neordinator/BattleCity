#pragma once

#include <glad/glad.h>

namespace Render
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer();
		~VertexBuffer();
		VertexBuffer(VertexBuffer&&) noexcept;
		VertexBuffer& operator=(VertexBuffer&&) noexcept;

		void init(const void*, const unsigned int);
		void update(const void*, const unsigned int) const;
		void bind() const;
		void unbind() const;

	private:
		GLuint m_id;
	};
}