#pragma once

#include <memory>

#include "Sprite.h"

namespace Render
{
	class Sprite;

	class SpriteAnimator
	{
	public:
		SpriteAnimator(std::shared_ptr<Sprite>);
		size_t getCurrentFrame() const { return m_currentFrame; }
		void update(const double delta);
		double getTotalDuration() const;
		void reset();

	private:
		std::shared_ptr<Sprite> m_pSprite;
		size_t m_currentFrame;
		double m_currentFrameDuration;
		double m_currentAnimationTime;
		double m_totalDuration;
	};
}