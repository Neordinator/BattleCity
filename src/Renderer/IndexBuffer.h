#pragma once

#include <glad/glad.h>

namespace Renderer
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		IndexBuffer();
		~IndexBuffer();
		IndexBuffer(IndexBuffer&&) noexcept;
		IndexBuffer& operator=(IndexBuffer&&) noexcept;

		void init(const void*, const unsigned int);
		void bind() const;
		void unbind() const;

	private:
		GLuint m_id;
	};
}