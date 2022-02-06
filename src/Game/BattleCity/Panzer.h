#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "../../Resources/ResourceManager.h"
#include "../IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace Render
{
	class Sprite;
}
class Panzer : public IGameObject
{
public:
	enum class EOrientation : uint8_t
	{
		Top,
		Bottom,
		Left,
		Right
	};

	Panzer(const float, const glm::vec2&, const glm::vec2&);

	void render() const override;
	void setOrientation(const EOrientation);
	void move(const bool);
	void update(const uint64_t) override;

private:
	EOrientation m_eOrientation;
	std::shared_ptr<Render::Sprite> m_pSprite_top;
	std::shared_ptr<Render::Sprite> m_pSprite_bottom;
	std::shared_ptr<Render::Sprite> m_pSprite_left;
	std::shared_ptr<Render::Sprite> m_pSprite_right;
	Render::SpriteAnimator m_spriteAnimator_top;
	Render::SpriteAnimator m_spriteAnimator_bottom;
	Render::SpriteAnimator m_spriteAnimator_left;
	Render::SpriteAnimator m_spriteAnimator_right;

	bool m_move;
	float m_velocity;
	glm::vec2 m_moveOffset;
};