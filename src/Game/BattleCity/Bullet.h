#pragma once

#include <memory>
#include <array>

#include "../IGameObject.h"
#include "../../Resources/ResourceManager.h"

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
	Bullet(const double, const glm::vec2&, const glm::vec2&, const float);

public:
	virtual void render() const override;
	bool isActive() const;
	void fire(const glm::vec2& position, const glm::vec2& direction);

private:
	EOrientation m_eOrientation;
	std::shared_ptr<Render::Sprite> m_pSprite_top;
	std::shared_ptr<Render::Sprite> m_pSprite_bottom;
	std::shared_ptr<Render::Sprite> m_pSprite_left;
	std::shared_ptr<Render::Sprite> m_pSprite_right;

	bool m_isActive;
};