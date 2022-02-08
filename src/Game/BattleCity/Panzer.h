#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "../../Resources/ResourceManager.h"
#include "../IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

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

public:
	Panzer(const double, const glm::vec2&, const glm::vec2&, const float);

public:
	void render() const override;
	void setOrientation(const EOrientation);
	void update(const double) override;
	double getMaxVelocity() const;
	void setVelocity(const double) override;

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

	std::shared_ptr<Render::Sprite> m_pSprite_respawn;
	Render::SpriteAnimator m_spriteAnimator_respawn;

	std::shared_ptr<Render::Sprite> m_pSprite_shield;
	Render::SpriteAnimator m_spriteAnimator_shield;

	Timer m_respawnTimer;
	Timer m_shieldTimer;

	bool m_isSpawning;
	bool m_hasShield;
	double m_maxVelocity;
};