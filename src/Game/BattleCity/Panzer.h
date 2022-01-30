#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "../../Renderer/AnimatedSprite.h"

namespace Render
{
	class AnimatedSprite;
}
class Panzer
{
public:
	enum class EOrientation
	{
		Top,
		Bottom,
		Left,
		Right
	};

	Panzer(std::shared_ptr<Render::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);

	void render() const;
	void setOrientation(const EOrientation eOrientation);
	void move(const bool move);
	void update(const uint64_t delta);

private:
	EOrientation m_eOrientation;
	std::shared_ptr<Render::AnimatedSprite> m_pSprite;
	bool m_move;
	float m_velocity;
	glm::vec2 m_position;
	glm::vec2 m_moveOffset;
};