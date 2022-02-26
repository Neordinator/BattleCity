#pragma once

#include <memory>
#include <array>

#include "../IGameObject.h"
#include "../../Resources/ResourceManager.h"
#include "../../System/Timer.h"
#include "../../Renderer/SpriteAnimator.h"

class Bullet : public IGameObject
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
	Bullet(const double, const glm::vec2&, const glm::vec2&, const glm::vec2&, const float);

public:
	virtual void render() const override;
	void update(const double) override;
	bool isActive() const;
	void fire(const glm::vec2& position, const glm::vec2& direction);
	virtual void onCollision() override;

private:
	glm::vec2 m_explosionSize;
	glm::vec2 m_explosionOffset;
	EOrientation m_eOrientation;
	std::shared_ptr<Render::Sprite> m_pSprite_top;
	std::shared_ptr<Render::Sprite> m_pSprite_bottom;
	std::shared_ptr<Render::Sprite> m_pSprite_left;
	std::shared_ptr<Render::Sprite> m_pSprite_right;
	std::shared_ptr<Render::Sprite> m_pSprite_explosion;
	Render::SpriteAnimator m_spriteAnimator_explosion;
	Timer m_explosionTimer;
	double m_maxVelocity;
	bool m_isActive;
	bool m_isExplosion;
};