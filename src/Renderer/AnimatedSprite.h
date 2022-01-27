#pragma once

#include <vector>

#include "Sprite.h"

namespace Renderer
{
	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(std::shared_ptr<Texture2D>, std::string, std::shared_ptr<ShaderProgram>, const glm::vec2&, const glm::vec2&, const float);

		void insertState(std::string, std::vector<std::pair<std::string, uint64_t>>);
		void update(const uint64_t delta);
		void setState(const std::string&);

		void render() const;

	private:
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDurations;
		mutable bool m_dirty = false;
	};
}