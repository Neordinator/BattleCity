#pragma once

#include <memory>

namespace Render
{
	class Sprite;

	class SpriteAnimator
	{
	public:
		SpriteAnimator(std::shared_ptr<Sprite>);
		size_t getCurrentFrame() const;
		void update(const double);
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