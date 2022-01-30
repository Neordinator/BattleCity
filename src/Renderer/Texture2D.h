#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

namespace Render
{
	struct SubTexture2D
	{
		glm::vec2 leftBottomUV;
		glm::vec2 rightTopUV;

		SubTexture2D(const glm::vec2&, const glm::vec2&);
		SubTexture2D();
	};
	class Texture2D
	{
	public:

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		Texture2D(const GLuint, GLuint, const unsigned char*, const unsigned int, const GLenum, const GLenum);
		~Texture2D();
		Texture2D(Texture2D&&) noexcept;
		Texture2D& operator=(Texture2D&&) noexcept;

		void bind() const;

		void addSubTexture(std::string, const glm::vec2&, const glm::vec2&);
		const SubTexture2D& getSubTexture(const std::string&) const;
		unsigned int width() const;
		unsigned int height() const;

	private:
		GLuint m_ID;
		GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;

		std::map<std::string, SubTexture2D> m_subTextures;
	};
}